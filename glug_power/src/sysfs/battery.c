#include "sysfs.h"

#include <dirent.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

static const char *power_root        = "/sys/class/power_supply";
static const char *bat_prefix       = "BAT";

static const char *bat_status_key   = "status";
static const char *bat_charging_val = "Charging";
static const char *bat_charged_val  = "Full";

static const char *bat_capacity_key = "capacity";
static const char *bat_whour_key    = "energy_now";
static const char *bat_watts_key     = "power_now";

enum
{
    bat_charging_len = 8,
    bat_charged_len  = 4
};

static void iterate_batteries(void (*callback)(DIR *, void *), void *context)
{
    struct dirent *ent;
    DIR *power_dir = opendir(power_root);
    if (power_dir)
    {
        while ((ent = readdir(power_dir)))
        {
            if (strncmp(ent->d_name, bat_prefix, 3) == 0)
            {
                int batdirfd = openat(dirfd(power_dir), ent->d_name, O_RDONLY);
                if (batdirfd != -1)
                {
                    DIR *batdir = fdopendir(batdirfd);
                    if (batdir)
                    {
                        callback(batdir, context);
                        closedir(batdir);
                    }
                    close(batdirfd);
                }
            }
        }

        closedir(power_dir);
    }
}

static void get_charge_state(DIR *batdir, void *context)
{
    struct battery_info *batinfo = context;

    int statusfd = openat(dirfd(batdir), bat_status_key, O_RDONLY);
    if (statusfd != -1)
    {
        FILE *fstatus = fdopen(statusfd, "r");
        if (fstatus)
        {
            char stat[bat_charging_len];
            fgets(stat, bat_charging_len, fstatus);

            if (strncmp(stat, bat_charging_val, bat_charging_len) == 0)
                ++batinfo->ncharging;
            else if (strncmp(stat, bat_charged_val, bat_charged_len) == 0)
                ++batinfo->ncharged;

            fclose(fstatus);
        }

        close(statusfd);
    }

    ++batinfo->count;
}

void battery_info(struct battery_info *batinfo)
{
    memset(batinfo, 0, sizeof(*batinfo));
    iterate_batteries(get_charge_state, batinfo);
}

struct battery_life
{
    int64_t total_life;
    size_t count;
};

static void get_battery_life(DIR *batdir, void *context)
{
    struct battery_life *batlife = context;

    int capacityfd = openat(dirfd(batdir), bat_capacity_key, O_RDONLY);
    if (capacityfd != -1)
    {
        FILE *fcapacity = fdopen(capacityfd, "r");
        if (fcapacity)
        {
            int life = -1;
            fscanf(fcapacity, "%d", &life);

            if (life > -1)
                batlife->total_life += life;

            fclose(fcapacity);
        }

        close(capacityfd);
    }
    ++batlife->count;
}

int8_t battery_life_percent(void)
{
    struct battery_life life = { 0, 0 };
    iterate_batteries(get_battery_life, &life);

    if (life.count == 0)
        return -1;
    return (int8_t)((uint64_t)life.total_life / life.count);
}

void get_battery_time(DIR *batdir, void *context)
{
    int32_t *battime = context;

    int whourfd = openat(dirfd(batdir), bat_whour_key, O_RDONLY);
    int wattsfd  = openat(dirfd(batdir), bat_watts_key, O_RDONLY);

    if (whourfd != -1 && wattsfd != -1)
    {
        FILE *fwhour = fdopen(whourfd, "r");
        FILE *fwatts = fdopen(wattsfd,  "r");
        if (fwhour && fwatts)
        {
            int whour = -1;
            int watts = -1;
            fscanf(fwhour, "%d", &whour);
            fscanf(fwatts,  "%d", &watts);

            int32_t time = -1;
            if (watts == 0)
                time = 0;
            else if (whour > -1 && watts > -1)
                time = whour * 60 * 60 / watts;

            if (*battime < time)
                *battime = time;

            fclose(fwatts);
            fclose(fwhour);
        }

        close(wattsfd);
        close(whourfd);
    }
}

int32_t battery_life_time(void)
{
    int32_t time = -1;
    iterate_batteries(get_battery_time, &time);

    return time;
}
