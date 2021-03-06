#include "power_platform.h"

#include "system_power_status/system_power_status.h"

glug_bool has_ac(void)
{
    return ac_connected();
}

size_t battery_count(void)
{
    return battery_connected();
}

size_t batteries_charging(const struct battery_list *list)
{
    (void) list;

    return battery_charging();
}

size_t batteries_charged(const struct battery_list *list)
{
    (void) list;

    return battery_charged();
}

int8_t avg_battery_pct(const struct battery_list *list)
{
    (void) list;

    return (int8_t)battery_life_percent();
}

int64_t max_battery_time(const struct battery_list *list)
{
    (void) list;

    return (int64_t)(int32_t)battery_life_time();
}
