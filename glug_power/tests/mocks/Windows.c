#include "Windows.h"

static SYSTEM_POWER_STATUS POWER_STATUS;

void set_ac_status(int8_t ac)
{
    POWER_STATUS.ACLineStatus = ac;
}

void set_battery_flag(int8_t flag)
{
    POWER_STATUS.BatteryFlag = flag;
}

void set_battery_life(int8_t life)
{
    POWER_STATUS.BatteryLifePercent = life;
}

void set_battery_time(int32_t time)
{
    POWER_STATUS.BatteryLifeTime = time;
}

void GetSystemPowerStatus(SYSTEM_POWER_STATUS *status)
{
    *status = POWER_STATUS;
}
