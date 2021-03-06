#include "power_platform.h"

#include "iops/iops.h"

glug_bool has_ac(void)
{
    return ac_connected();
}

size_t battery_count(void)
{
    return batteries_count();
}

size_t batteries_charging(const struct battery_list *list)
{
    return ncharging(list);
}

size_t batteries_charged(const struct battery_list *list)
{
    return ncharged(list);
}

int8_t avg_battery_pct(const struct battery_list *list)
{
    return (int8_t)battery_life_percent(list);
}

int64_t max_battery_time(const struct battery_list *list)
{
    return (int64_t)(int32_t)battery_life_time(list);
}
