#include <glug/power/power.h>
#include <glug/power/battery_status.h>
#include <glug/power/power_supply.h>
#include "battery_node.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

static const char *power_root        = "/sys/class/power_supply";
static const char *ac_prefix         = "ACAD";
static const char *ac_online_file    = "online";
static const char *batt_prefix       = "BAT";
static const char *batt_status_key   = "status";
static const char *batt_percent_key  = "capacity";
static const char *batt_whour_key    = "energy_now";
static const char *batt_watt_key     = "power_now";
static const char *batt_charging_val = "Charging";
static const char *batt_charged_val  = "Full";

// add strlens of all the above strings in an enum to use as array sizes
enum {
    power_root_len    = 23,
    ac_prefix_len     = 4,
    ac_online_len     = 6,
    batt_prefix_len   = 3,
    batt_status_len   = 6,
    batt_percent_len  = 8,
    batt_whour_len    = 10,
    batt_watt_len     = 9,
    batt_charging_len = 8,
    batt_charged_len  = 4,
};

static FILE *open_power_file(const char *pow_src, const char *key)
{
    size_t pow_src_len = strlen(pow_src);
    size_t key_len = strlen(key);
    char *full_src = malloc(power_root_len + pow_src_len + key_len + 3);
    FILE *stat = NULL;

    strcpy(full_src, power_root);
    full_src[power_root_len] = '/';
    strcpy(full_src + power_root_len + 1, pow_src);
    full_src[power_root_len + pow_src_len + 1] = '/';
    strcpy(full_src + power_root_len + pow_src_len + 2, key);
    full_src[power_root_len + pow_src_len + key_len + 2] = '\0';

    stat = fopen(full_src, "r");

    free(full_src);
    return stat;
}

static long pow_src_stat(const char *pow_src, const char *key)
{
    long val = -1;
    char data[sizeof(long)];
    FILE *stat = open_power_file(pow_src, key);

    if (stat)
        val = strtol(fgets(data, sizeof(long), stat), NULL, 10);

    fclose(stat);
    return val;
}

static void pow_src_string(char *res, int res_length, const char *pow_src, const char *key)
{
    FILE *stat = open_power_file(pow_src, key);

    if (stat)
        fgets(res, res_length, stat);

    fclose(stat);
}

static size_t battery_count()
{
    size_t count = 0;
    struct dirent *ent;
    DIR *power_dir = opendir(power_root);
    if (power_dir)
        for (; (ent = readdir(power_dir));)
            if (strstr(ent->d_name, batt_prefix) == ent->d_name)
                ++count;

    closedir(power_dir);
    return count;
}

static struct battery_name_node *battery_names(size_t *count)
{
    struct battery_name_node batteries, *current = &batteries;
    size_t bat_count;
    struct dirent *ent;
    DIR *power_dir = opendir(power_root);

    for(; power_dir && (ent = readdir(power_dir));)
        if (strstr(ent->d_name, batt_prefix) == ent->d_name)
        {
            current = current->next = create_battery_node(ent->d_name);
            bat_count++;
        }

    closedir(power_dir);

    if (count) *count = bat_count;
    return batteries.next;
}

static size_t batteries_charging(const struct battery_name_node *batteries)
{
    size_t is_charging = 0;
    char res[batt_charging_len + 1];
    const struct battery_name_node *current;

    res[batt_charging_len] = '\0';
    for(current = batteries; !is_charging && current; current = current->next)
    {
        pow_src_string(res, batt_charging_len + 1, current->name, batt_status_key);
        if (!strcmp(res, batt_charging_val))
            ++is_charging;
    }

    return is_charging;
}

static size_t batteries_charged(const struct battery_name_node *batteries)
{
    size_t is_charged = 0;
    char res[batt_charged_len + 1];
    const struct battery_name_node *current;

    res[batt_charged_len] = '\0';
    for(current = batteries; is_charged && current; current = current->next)
    {
        pow_src_string(res, batt_charged_len + 1, current->name, batt_status_key);
        if (!strcmp(res, batt_charged_val))
            ++is_charged;
    }

    return is_charged;
}

enum power_supply GLUG_LIB_API power_state()
{
    if (pow_src_stat(ac_prefix, ac_online_file) > 0) return ps_ac;
    if (battery_count() > 0)                         return ps_battery;
    return ps_unknown;
}

enum battery_status GLUG_LIB_API battery_state()
{
    size_t battery_count;
    struct battery_name_node *batteries = battery_names(&battery_count);
    const int has_ac = pow_src_stat(ac_prefix, ac_online_file) > 0;
    const int has_battery = batteries != NULL;
    enum battery_status status = bs_unknown;

    if (!has_battery && has_ac)                             status = bs_none;
    else if (has_battery && !has_ac)                        status = bs_discharging;
    else if (batteries_charging(batteries))                 status = bs_charging;
    else if (batteries_charged(batteries) == battery_count) status = bs_charged;

    free_battery_list(batteries);
    return status;
}

int8_t GLUG_LIB_API battery_pct()
{
    int total_cap = 0;
    size_t battery_count;
    struct battery_name_node *current, *batteries = battery_names(&battery_count);

    if (!batteries) return -1;

    for(current = batteries; current; current = current->next)
    {
        long capacity = pow_src_stat(current->name, batt_percent_key);
        ++battery_count;

        if (capacity > -1)
            total_cap += capacity;
    }

    free_battery_list(batteries);
    return (char)(total_cap * 1.0 / battery_count);
}

int64_t GLUG_LIB_API battery_time()
{
    int64_t remaining_time = -1;
    struct battery_name_node *current, *batteries;

    if (pow_src_stat(ac_prefix, ac_online_file) > 0) return -1;

    batteries = battery_names(NULL);
    if (!batteries) return -1;

    for(current = batteries; current; current = current->next)
    {
        long watts = pow_src_stat(current->name, batt_watt_key);
        long watthours = pow_src_stat(current->name, batt_whour_key);

        if (watts > 0 && watthours > 0)
        {
            int64_t curr_rem = watthours * 60ll * 60 / watts;
            remaining_time = remaining_time > curr_rem ? remaining_time : curr_rem;
        }
    }

    free_battery_list(batteries);
    return remaining_time;
}
