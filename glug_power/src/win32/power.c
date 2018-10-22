#include "../power_platform.h"
#include "../battery_platform.h"
#include "../battery_list.h"
#include <glug/power/battery_status.h>
#include <glug/power/power_supply.h>

#include <Windows.h>

static const unsigned char bat_charging = 1 << 3;
static const unsigned char bat_missing = 1 << 7;
static const unsigned char bat_unknown = (unsigned char)-1;

static int has_battery(SYSTEM_POWER_STATUS *ps)
{
    return !(ps->BatteryFlag == bat_unknown || ps->BatteryFlag & bat_missing);
}

int GLUG_LIB_LOCAL has_ac()
{
    SYSTEM_POWER_STATUS ps;
    GetSystemPowerStatus(&ps);

    return ps.ACLineStatus == 1;
}

struct battery_list GLUG_LIB_LOCAL battery_list()
{
    struct battery_list list = { .batteries = NULL, .count = 0 };
    SYSTEM_POWER_STATUS ps;
    GetSystemPowerStatus(&ps);

    list.count = (size_t)has_battery(&ps);
    return list;
}

size_t GLUG_LIB_LOCAL battery_count()
{
    SYSTEM_POWER_STATUS ps;
    GetSystemPowerStatus(&ps);

    return has_battery(&ps) ? 1 : 0;
}

size_t GLUG_LIB_LOCAL batteries_charging(const struct battery_list *list)
{
    SYSTEM_POWER_STATUS ps;
    GetSystemPowerStatus(&ps);
    (void) list;

    return has_battery(&ps) && ps.BatteryFlag & bat_charging ? 1 : 0;
}

size_t GLUG_LIB_LOCAL batteries_charged (const struct battery_list *list)
{
    SYSTEM_POWER_STATUS ps;
    GetSystemPowerStatus(&ps);
    (void) list;

    return ps.ACLineStatus == 1 &&
           has_battery(&ps) &&
           ps.BatteryFlag != bat_charging ? 1 : 0;
}

int8_t GLUG_LIB_LOCAL avg_battery_pct (const struct battery_list *list)
{
    SYSTEM_POWER_STATUS ps;
    GetSystemPowerStatus(&ps);
    (void) list;

    return (int8_t)ps.BatteryLifePercent;
}

int64_t GLUG_LIB_LOCAL max_battery_time(const struct battery_list *list)
{
    SYSTEM_POWER_STATUS ps;
    GetSystemPowerStatus(&ps);
    (void) list;

    // cast to 32bit to report a proper -1ll instead of ULONG_MAX
    return (int64_t)(int32_t)ps.BatteryLifeTime;
}
