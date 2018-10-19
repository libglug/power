#include <glug/power/power.h>
#include <glug/power/battery_status.h>
#include <glug/power/power_supply.h>

#include <Windows.h>

static const unsigned char bat_ = 1 << 0 | 1 << 1 | 1 << 2;
static const unsigned char bat_charging = 1 << 3;
static const unsigned char bat_missing = 1 << 7;
static const unsigned char bat_unknown = (1 << 8) - 1;

enum power_supply GLUG_LIB_API power_state()
{
    SYSTEM_POWER_STATUS ps;
    GetSystemPowerStatus(&ps);

    if (ps.ACLineStatus == 1) return ps_ac;
    if ((ps.BatteryFlag & bat_missing) != bat_missing) return ps_battery;
    return ps_unknown;
}

enum battery_status GLUG_LIB_API battery_state()
{
    SYSTEM_POWER_STATUS ps;
    GetSystemPowerStatus(&ps);

    if ((ps.BatteryFlag & bat_unknown) == bat_unknown) return bs_unknown;
    if (ps.BatteryFlag & bat_missing)                  return bs_none;
    if (ps.BatteryFlag & bat_charging)                 return bs_charging;
    if (ps.BatteryFlag & bat_ && ps.ACLineStatus != 1) return bs_discharging;
    return bs_charged;
}

int8_t GLUG_LIB_API battery_pct()
{
    SYSTEM_POWER_STATUS ps;
    GetSystemPowerStatus(&ps);

    return (int8_t)ps.BatteryLifePercent;
}

int64_t GLUG_LIB_API battery_time()
{
    SYSTEM_POWER_STATUS ps;
    GetSystemPowerStatus(&ps);

    // cast to 32bit to report a proper -1ll instead of ULONG_MAX
    return (int32_t)ps.BatteryLifeTime;
}

