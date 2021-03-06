#include "../power_platform.h"
#include "../battery_platform.h"
#include "../battery_list.h"
#include <glug/power/battery_status.h>
#include <glug/power/power_supply.h>

#include <Windows.h>

static int has_battery(SYSTEM_POWER_STATUS *ps)
{
    return !(ps->BatteryFlag == BATTERY_FLAG_UNKNOWN || ps->BatteryFlag & BATTERY_FLAG_NO_BATTERY);
}

struct battery_list battery_list(void)
{
    struct battery_list list = { .count = 0 , .batteries = NULL };
    SYSTEM_POWER_STATUS ps;
    GetSystemPowerStatus(&ps);

    list.count = (size_t)has_battery(&ps);
    return list;
}
