#include <glug/power.h>
#include "battery_list.h"
#include "power_platform.h"

#include <stdint.h>
#include <stddef.h>

enum glug_power_supply GLUG_LIB_API glug_power_state()
{
    if(has_ac())             return glug_ps_ac;
    if (battery_count() > 0) return glug_ps_battery;
    return glug_ps_unknown;
}

enum glug_battery_status GLUG_LIB_API glug_battery_state()
{
    struct battery_list batteries = battery_list();
    enum glug_battery_status status = glug_bs_unknown;
    int ac = has_ac();

    if (!batteries.count && ac)
        status = glug_bs_none;
    else if (batteries.count)
    {
        if (!ac)
            status = glug_bs_discharging;
        else if (batteries_charging(&batteries) > 0)
            status = glug_bs_charging;
        else if (batteries_charged(&batteries) == batteries.count)
            status = glug_bs_charged;
    }

    free_battery_list(&batteries);
    return status;
}

int8_t GLUG_LIB_API glug_battery_pct()
{
    struct battery_list batteries = battery_list();
    int8_t pct = avg_battery_pct(&batteries);

    free_battery_list(&batteries);
    return pct;
}

int64_t GLUG_LIB_API glug_battery_time()
{
    struct battery_list batteries = battery_list();
    int64_t time = max_battery_time(&batteries);

    free_battery_list(&batteries);
    return time;
}
