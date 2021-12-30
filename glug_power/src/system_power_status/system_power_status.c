#include "system_power_status.h"
#include <stdint.h>

#include <glug/bool_t.h>

#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

enum ac_line_state ac_line_status(void)
{
    SYSTEM_POWER_STATUS ps;
    GetSystemPowerStatus(&ps);

    return ps.ACLineStatus;
}

enum battery_flag battery_flag(void)
{
    SYSTEM_POWER_STATUS ps;
    GetSystemPowerStatus(&ps);

    return (uint8_t)ps.BatteryFlag;
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
