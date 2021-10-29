#include "power_bridge.h"

#include "battery_state_t.h"
#include "iops/iops.h"

#include <glug/bool_t.h>

typedef void (*battery_callback)(const struct battery *, void *);

struct running_average
{
    int8_t avg;
    int8_t count;
};

glug_bool_t has_ac(void)
{
    return providing_power_source_type() == iops_ac;
}

static void count_batteries(const struct battery *source, size_t *count)
{
    ++*count;
}

void battery_count(size_t *count)
{
    iterate_batteries((battery_callback)count_batteries, count);
}

static void get_battery_states(const struct battery *source, struct battery_state *state)
{
    ++state->count;

    glug_bool_t bat_charging = battery_is_charging(source);
    if (bat_charging)
        ++state->ncharging;
    else
    {
        glug_bool_t bat_charged = battery_is_charged(source);
        if (bat_charged)
            ++state->ncharged;
    }
}

void battery_state(struct battery_state *state)
{
    iterate_batteries((battery_callback)get_battery_states, state);
}

static void avg_battery_levels(const struct battery *source, struct running_average *battery_average)
{
    int32_t cap = battery_capacity(source);
    int32_t max_cap = battery_max_capacity(source);

    // if the max_cap is -1 or 0, don't consider it
    if (max_cap > 0)
    {
        ++battery_average->count;
        int8_t battery_level = cap * 100 / max_cap;
        battery_average->avg += (battery_level - battery_average->avg) / battery_average->count;
    }
}

int8_t battery_level()
{
    struct running_average battery_average = { 0, 0 };
    iterate_batteries((battery_callback)avg_battery_levels, &battery_average);

    return battery_average.avg;
}

static void max_battery_times(const struct battery *source, int32_t *max_time)
{
    glug_bool_t bat_charging = battery_is_charging(source);
    glug_bool_t bat_charged  = battery_is_charged(source);
    int32_t bat_time         = battery_time_to_empty(source);

    // if the battery is charging or no time was reported, don't consider it
    if (bat_charging || bat_time < 0) return;

    // fully charged batteries with AC still report 0 time to empty
    if (bat_time == 0 && bat_charged) return;

    // convert bat_time to sec
    bat_time *= 60;
    *max_time = *max_time > bat_time ? *max_time : bat_time;
}

int32_t battery_time()
{
    int32_t time = -1;
    iterate_batteries((battery_callback)max_battery_times, &time);

    return time;
}
