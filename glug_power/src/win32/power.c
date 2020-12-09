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

int has_ac(void)
{
    SYSTEM_POWER_STATUS ps;
    GetSystemPowerStatus(&ps);

    return ps.ACLineStatus == AC_LINE_ONLINE;
}

struct battery_list battery_list(void)
{
    struct battery_list list = { .batteries = NULL, .count = 0 };
    SYSTEM_POWER_STATUS ps;
    GetSystemPowerStatus(&ps);

    list.count = (size_t)has_battery(&ps);
    return list;
}

size_t battery_count(void)
{
    SYSTEM_POWER_STATUS ps;
    GetSystemPowerStatus(&ps);

    return has_battery(&ps) ? 1 : 0;
}

size_t batteries_charging(const struct battery_list *list)
{
    SYSTEM_POWER_STATUS ps;
    GetSystemPowerStatus(&ps);
    (void) list;

    return has_battery(&ps) && ps.BatteryFlag & BATTERY_FLAG_CHARGING ? 1 : 0;
}

size_t batteries_charged (const struct battery_list *list)
{
    SYSTEM_POWER_STATUS ps;
    GetSystemPowerStatus(&ps);
    (void) list;

    return ps.ACLineStatus == AC_LINE_ONLINE &&
           has_battery(&ps) &&
           ps.BatteryFlag != BATTERY_FLAG_CHARGING ? 1 : 0;
}

int8_t avg_battery_pct (const struct battery_list *list)
{
    SYSTEM_POWER_STATUS ps;
    GetSystemPowerStatus(&ps);
    (void) list;

    return (int8_t)ps.BatteryLifePercent;
}

int64_t max_battery_time(const struct battery_list *list)
{
    SYSTEM_POWER_STATUS ps;
    GetSystemPowerStatus(&ps);
    (void) list;

    // cast to 32bit to report a proper -1ll instead of ULONG_MAX
    return (int64_t)(int32_t)ps.BatteryLifeTime;
}
