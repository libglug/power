#include "power_bridge.h"

#include "battery_state_t.h"
#include "iops/iops.h"

glug_bool has_ac(void)
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

int8_t battery_pct()
{
    return (int8_t)battery_life_percent();
}

int64_t battery_time()
{
    return (int64_t)battery_life_time();
}
