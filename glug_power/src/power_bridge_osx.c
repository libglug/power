#include "power_bridge.h"

#include "battery_state_t.h"
#include "iops/iops.h"

#include <glug/bool_t.h>

glug_bool_t has_ac(void)
{
    return ac_connected();
}

void battery_count(size_t *count)
{
    struct battery_info batteries;
    battery_info(&batteries);

    *count = batteries.count;
}

void battery_state(struct battery_state *state)
{
    struct battery_info batteries;
    battery_info(&batteries);

    state->count     = batteries.count;
    state->ncharging = batteries.ncharging;
    state->ncharged  = batteries.ncharged;
}

int8_t battery_level()
{
    return (int8_t)battery_life_percent();
}

int32_t battery_time()
{
    return battery_life_time();
}
