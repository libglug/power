#include <glug/power.h>
#include "battery_list.h"
#include "power_platform.h"

#include <stdint.h>
#include <stddef.h>

enum glug_power_supply glug_power_active_supply(void)
{
    if (has_ac())            return glug_power_ac;
    if (battery_count() > 0) return glug_power_battery;
    return glug_power_unknown;
}

enum glug_battery_status glug_power_battery_state(void)
{
    struct battery_list batteries = battery_list();
    enum glug_battery_status status = glug_battery_unknown;
    glug_bool ac = has_ac();

    if (!batteries.count && ac)
        status = glug_battery_none;
    else if (batteries.count)
    {
        if (!ac)
            status = glug_battery_discharging;
        else if (batteries_charging(&batteries) > 0)
            status = glug_battery_charging;
        else if (batteries_charged(&batteries) == batteries.count)
            status = glug_battery_charged;
    }

    free_battery_list(&batteries);
    return status;
}

int8_t glug_power_battery_pct(void)
{
    struct battery_list batteries = battery_list();
    int8_t pct = avg_battery_pct(&batteries);

    free_battery_list(&batteries);
    return pct;
}

int64_t glug_power_battery_time(void)
{
    struct battery_list batteries = battery_list();
    int64_t time = max_battery_time(&batteries);

    free_battery_list(&batteries);
    return time;
}
