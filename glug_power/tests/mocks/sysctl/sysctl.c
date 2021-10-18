#include "sysctl.h"

static glug_bool_t AC = glug_true;
void set_ac_connected(glug_bool_t connected)
{
    AC = connected;
}

glug_bool_t ac_connected(void)
{
    return AC;
}

static glug_bool_t BATT = glug_true;
void set_battery_connected(glug_bool_t connected)
{
    BATT = connected;
}

glug_bool_t battery_connected(void)
{
    return BATT;
}

static enum charge_state CHARGE_STATE = cs_unknown;
void set_charge_state(enum charge_state state)
{
    CHARGE_STATE = state;
}

enum charge_state battery_charge_state(void)
{
    return CHARGE_STATE;
}

static int8_t LIFE = -1;
void set_battery_life(int8_t life)
{
    LIFE = life;
}

int8_t battery_life_percent(void)
{
    return LIFE;
}

static int32_t TIME = -1;
void set_battery_time(int32_t time)
{
    TIME = time;
}

int32_t battery_life_time(void)
{
    return TIME;
}
