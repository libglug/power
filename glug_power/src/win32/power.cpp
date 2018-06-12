#include <glug/power/power.h>
#include <glug/power/battery_status.h>
#include <glug/power/power_supply.h>

#include <windows.h>

namespace glug
{

static const unsigned char bat_ = 1 << 0 | 1 << 1 | 1 << 2;
static const unsigned char bat_charging = 1 << 3;
static const unsigned char bat_missing = 1 << 7;
static const unsigned char bat_unknown = (1 << 8) - 1;

power_supply power_state()
{
    SYSTEM_POWER_STATUS ps;
    GetSystemPowerStatus(&ps);

    if (ps.ACLineStatus == 1) return ps_ac;
    if ((ps.BatteryFlag & bat_missing) != bat_missing) return ps_battery;
    return ps_unknown;
}

battery_status battery_state()
{

    SYSTEM_POWER_STATUS ps;
    GetSystemPowerStatus(&ps);

    if ((ps.BatteryFlag & bat_unknown) == bat_unknown) return bs_unknown;
    if (ps.BatteryFlag & bat_missing)                  return bs_none;
    if (ps.BatteryFlag & bat_charging)                 return bs_charging;
    if (ps.BatteryFlag & bat_ && ps.ACLineStatus != 1) return bs_discharging;
    return bs_charged;
}

char battery_pct()
{
    SYSTEM_POWER_STATUS ps;
    GetSystemPowerStatus(&ps);

    return ps.BatteryLifePercent;
}

long long battery_time()
{
    SYSTEM_POWER_STATUS ps;
    GetSystemPowerStatus(&ps);

    return ps.BatteryLifeTime;
}

} // namespace glug
