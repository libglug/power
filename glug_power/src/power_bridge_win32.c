#include "power_bridge.h"

#include "battery_state_t.h"
#include "system_power_status/system_power_status.h"

glug_bool has_ac(void)
{
    return ac_connected();
}

void battery_count(size_t *count)
{
    *count = battery_connected();
}

void battery_state(struct battery_state *state)
{
    enum charge_state charge_state = battery_charge_state();

    state->count = charge_state != cs_unknown && charge_state != cs_none;
    state->ncharged = charge_state == cs_charged;
    state->ncharging = charge_state == cs_charging;
}

int8_t battery_pct(void)
{
    return battery_life_percent();
}

int64_t battery_time(void)
{
    return (int64_t)battery_life_time();
}
