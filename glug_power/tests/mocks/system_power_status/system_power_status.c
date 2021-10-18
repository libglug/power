#include "system_power_status.h"

static glug_bool_t AC = glug_true;
void set_ac_connected(glug_bool_t ac)
{
    AC = ac;
}

glug_bool_t ac_connected(void)
{
    return AC;
}


static glug_bool_t BATT = glug_false;
void set_battery_connected(glug_bool_t batt)
{
    BATT = batt;
}

glug_bool_t battery_connected(void)
{
    return BATT;
}

static enum charge_state CHARGE_STATE = cs_none;
void set_charge_state(enum charge_state state)
{
    CHARGE_STATE = state;
}

enum charge_state battery_charge_state(void)
{
    return CHARGE_STATE;
}

static int8_t BATT_LEVEL = -1;
void set_battery_life(int8_t level)
{
    BATT_LEVEL = level;
}

int8_t battery_life_percent(void)
{
    return BATT_LEVEL;
}

static int32_t BATT_TIME = -1;
void set_battery_time(int32_t time)
{
    BATT_TIME = time;
}

int32_t battery_life_time(void)
{
    return BATT_TIME;
}
