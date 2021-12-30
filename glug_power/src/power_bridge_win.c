#include "power_bridge.h"

#include "battery_state_t.h"
#include "system_power_status/system_power_status.h"

#include <glug/bool_t.h>

glug_bool_t has_ac(void)
{
    return ac_line_status() == ac_online;
}

void battery_count(size_t *count)
{
    uint8_t flags = battery_flag();
    *count = !(flags == bf_unknown || flags & bf_none);
}

void battery_state(struct battery_state *state)
{
    uint8_t flags = battery_flag();

    state->count = flags != bf_unknown && flags != bf_none;
    state->ncharging = state->count && flags == bf_charging;
    state->ncharged = state->count && flags != bf_charging;
}

int8_t battery_level(void)
{
    return battery_life_percent();
}

int32_t battery_time(void)
{
    return battery_life_time();
}
