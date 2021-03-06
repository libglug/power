#include "system_power_status.h"

#include <glug/bool.h>

#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

static glug_bool has_battery(const SYSTEM_POWER_STATUS *ps)
{
    return !(ps->BatteryFlag == BATTERY_FLAG_UNKNOWN || ps->BatteryFlag & BATTERY_FLAG_NO_BATTERY);
}

glug_bool ac_connected(void)
{
    SYSTEM_POWER_STATUS ps;
    GetSystemPowerStatus(&ps);

    return ps.ACLineStatus == AC_LINE_ONLINE;
}

glug_bool battery_connected(void)
{
    SYSTEM_POWER_STATUS ps;
    GetSystemPowerStatus(&ps);

    return has_battery(&ps);
}

glug_bool battery_charging(void)
{
    SYSTEM_POWER_STATUS ps;
    GetSystemPowerStatus(&ps);

    return has_battery(&ps) && (ps.BatteryFlag & BATTERY_FLAG_CHARGING);
}

glug_bool battery_charged(void)
{
    SYSTEM_POWER_STATUS ps;
    GetSystemPowerStatus(&ps);

    return ps.ACLineStatus == AC_LINE_ONLINE &&
           has_battery(&ps) &&
           ps.BatteryFlag != BATTERY_FLAG_CHARGING;
}

uint8_t battery_life_percent(void)
{
    SYSTEM_POWER_STATUS ps;
    GetSystemPowerStatus(&ps);

    return ps.BatteryLifePercent;
}

uint32_t battery_life_time(void)
{
    SYSTEM_POWER_STATUS ps;
    GetSystemPowerStatus(&ps);

    return ps.BatteryLifeTime;
}
