#include "power_bridge.h"

static glug_bool_t AC = glug_true;

void set_ac(glug_bool_t ac)
{
    AC = ac;
}

glug_bool_t has_ac(void)
{
    return AC;
}

static struct battery_state BATTS = {0, 0, 0};

void battery_count(size_t *nbatt)
{
    *nbatt = BATTS.count;
}

void set_batteries(size_t nbatts)
{
    BATTS.count = nbatts;
}

void set_charging_batteries(size_t ncharging)
{
    BATTS.ncharging = ncharging;
}

void set_charged_batteries(size_t ncharged)
{
    BATTS.ncharged = ncharged;
}

void battery_state(struct battery_state *state)
{
    *state = BATTS;
}

static int8_t BATT_LEVEL = 100;

void set_battery_level(int8_t level)
{
    BATT_LEVEL = level;
}

int8_t battery_level(void)
{
    return BATT_LEVEL;
}

static int32_t BATT_TIME = (4 * 60 + 30) * 60 + 44;

void set_battery_time(int32_t time)
{
    BATT_TIME = time;
}

int32_t battery_time(void)
{
    return BATT_TIME;
}
