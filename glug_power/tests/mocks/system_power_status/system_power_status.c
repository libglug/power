#include "system_power_status.h"

static enum ac_line_state AC_LINE_STATE = ac_online;
void set_ac_line_status(enum ac_line_state state)
{
    AC_LINE_STATE = state;
}

enum ac_line_state ac_line_status(void)
{
    return AC_LINE_STATE;
}

static enum battery_flag BATTERY_FLAGS = bf_none;
void set_battery_flag(enum battery_flag flags)
{
    BATTERY_FLAGS = flags;
}

enum battery_flag battery_flag(void)
{
    return BATTERY_FLAGS;
}

static int8_t BATTERY_CHARGE = 0;
void set_battery_percent(int8_t pct)
{
    BATTERY_CHARGE = pct;
}

int8_t battery_life_percent(void)
{
    return BATTERY_CHARGE;
}

static int32_t BATTERY_TIME = 0;
void set_battery_time(int32_t time)
{
    BATTERY_TIME = time;
}

int32_t battery_life_time(void)
{
    return BATTERY_TIME;
}

