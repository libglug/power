#include <glug/power/power.h>
#include "power_bridge.h"

#include <stdint.h>
#include <stddef.h>

#include <glug/bool_t.h>
#include "battery_state_t.h"

enum glug_power_supply glug_power_active_supply(void)
{
    if (has_ac())            return glug_power_ac;

    size_t nbatts;
    battery_count(&nbatts);
    if (nbatts > 0) return glug_power_battery;

    return glug_power_unknown;
}

enum glug_battery_status glug_power_battery_state(void)
{
    struct battery_state batteries;
    battery_state(&batteries);

    enum glug_battery_status status = glug_battery_unknown;
    glug_bool_t ac = has_ac();

    if (!batteries.count && ac)
        status = glug_battery_none;
    else if (batteries.count)
    {
        if (!ac)
            status = glug_battery_discharging;

        else if (batteries.ncharging > 0)
            status = glug_battery_charging;

        else if (batteries.ncharged == batteries.count)
            status = glug_battery_charged;
    }

    return status;
}

int8_t glug_power_battery_level(void)
{
    return battery_level();
}

int32_t glug_power_battery_time(void)
{
    return battery_time();
}
