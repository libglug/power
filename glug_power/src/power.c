#include <glug/power.h>
#include "battery_list.h"
#include "power_platform.h"

#include <stdint.h>
#include <stddef.h>

enum power_supply GLUG_LIB_API power_state()
{
    if(has_ac())             return ps_ac;
    if (battery_count() > 0) return ps_battery;
    return ps_unknown;
}

enum battery_status GLUG_LIB_API battery_state()
{
    struct battery_list batteries = battery_list();
    enum battery_status status = bs_unknown;
    int ac = has_ac();

    if (!batteries.count && ac)
        status = bs_none;
    else if (batteries.count)
    {
        if (!ac)
            status = bs_discharging;
        else if (batteries_charging(&batteries) > 0)
            status = bs_charging;
        else if (batteries_charged(&batteries) == batteries.count)
            status = bs_charged;
    }

    free_battery_list(&batteries);
    return status;
}

int8_t GLUG_LIB_API battery_pct()
{
    struct battery_list batteries = battery_list();
    int8_t pct = avg_battery_pct(&batteries);

    free_battery_list(&batteries);
    return pct;
}

int64_t GLUG_LIB_API battery_time()
{
    struct battery_list batteries = battery_list();
    int64_t time = max_battery_time(&batteries);

    free_battery_list(&batteries);
    return time;
}
