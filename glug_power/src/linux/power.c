#include "../power_platform.h"
#include "../battery_platform.h"
#include "../battery_list.h"
#include <glug/power/battery_status.h>
#include <glug/power/power_supply.h>

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
    long_digit_len    = 10,
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
    char data[long_digit_len + 1];
    FILE *stat = open_power_file(pow_src, key);

    if (stat)
        val = strtol(fgets(data, long_digit_len + 1, stat), NULL, 10);

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

int has_ac(void)
{
    return pow_src_stat(ac_prefix, ac_online_file) > 0;
}

struct battery_list battery_list(void)
{
    struct battery_list batt_list = { .batteries = NULL, .count = 0 };
    struct battery_info_node batteries, *current;
    struct dirent *ent;
    DIR *power_dir = opendir(power_root);

    batteries.next = NULL;
    current = &batteries;

    for(; power_dir && (ent = readdir(power_dir));)
        if (strstr(ent->d_name, batt_prefix) == ent->d_name)
        {
            current = current->next = create_battery_node(ent->d_name);
            ++batt_list.count;
        }

    closedir(power_dir);

    batt_list.batteries = batteries.next;
    return batt_list;
}

size_t battery_count(void)
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

size_t batteries_charging(const struct battery_list *batt_list)
{
    size_t is_charging = 0;
    char res[batt_charging_len + 1];
    const struct battery_info_node *current;

    if (!batt_list) return is_charging;
    res[batt_charging_len] = '\0';

    for(current = batt_list->batteries; current; current = current->next)
    {
        pow_src_string(res, batt_charging_len + 1, current->info, batt_status_key);
        if (!strcmp(res, batt_charging_val))
            ++is_charging;
    }

    return is_charging;
}

size_t batteries_charged(const struct battery_list *batt_list)
{
    size_t is_charged = 0;
    char res[batt_charged_len + 1];
    const struct battery_info_node *current;

    if (!batt_list) return is_charged;
    res[batt_charged_len] = '\0';
    for(current = batt_list->batteries; current; current = current->next)
    {
        pow_src_string(res, batt_charged_len + 1, current->info, batt_status_key);
        if (!strcmp(res, batt_charged_val))
            ++is_charged;
    }

    return is_charged;
}

int8_t avg_battery_pct(const struct battery_list *batt_list)
{
    long long total_cap = 0;
    struct battery_info_node *current;

    if (!batt_list || !batt_list->count) return (int8_t)-1;

    for(current = batt_list->batteries; current; current = current->next)
    {
        long capacity = pow_src_stat(current->info, batt_percent_key);

        if (capacity > -1)
            total_cap += capacity;
    }

    return (int8_t)(total_cap * 1.0 / batt_list->count);
}

int64_t max_battery_time(const struct battery_list *batt_list)
{
    int64_t remaining_time = 0;
    struct battery_info_node *current;

    if (has_ac() || !batt_list || !batt_list->count) return -1ll;

    for(current = batt_list->batteries; current; current = current->next)
    {
        long watthours = pow_src_stat(current->info, batt_whour_key);
        long watts = pow_src_stat(current->info, batt_watt_key);

        if (watts > 0 && watthours > 0)
        {
            int64_t curr_rem = watthours * 60 * 60 / watts;
            remaining_time = remaining_time > curr_rem ? remaining_time : curr_rem;
        }
    }

    return remaining_time;
}
