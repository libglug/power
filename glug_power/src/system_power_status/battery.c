#include "system_power_status.h"

#include <glug/bool.h>

#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

static glug_bool has_battery(const SYSTEM_POWER_STATUS *ps)
{
    return !(ps->BatteryFlag == BATTERY_FLAG_UNKNOWN || ps->BatteryFlag & BATTERY_FLAG_NO_BATTERY);
}

glug_bool battery_connected(void)
{
    SYSTEM_POWER_STATUS ps;
    GetSystemPowerStatus(&ps);

    return has_battery(&ps);
}

enum charge_state battery_charge_state()
{
    SYSTEM_POWER_STATUS ps;
    GetSystemPowerStatus(&ps);

    if (!has_battery(&ps)) return cs_none;
    if (ps.BatteryFlag & BATTERY_FLAG_CHARGING) return cs_charging;
    if (ps.ACLineStatus == AC_LINE_ONLINE) return cs_charged;

    return cs_unknown;
}

int8_t battery_life_percent(void)
{
    SYSTEM_POWER_STATUS ps;
    GetSystemPowerStatus(&ps);

    return ps.BatteryLifePercent;
}

int32_t battery_life_time(void)
{
    SYSTEM_POWER_STATUS ps;
    GetSystemPowerStatus(&ps);

    return ps.BatteryLifeTime;
}
