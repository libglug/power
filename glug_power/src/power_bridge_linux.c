#include "power_bridge.h"

#include "battery_state_t.h"
#include "sysfs/sysfs.h"

glug_bool has_ac(void)
{
    return ac_connected();
}

void battery_count(size_t *count)
{
    struct battery_info info;
    battery_info(&info);

    *count = info.count;
}

void battery_state(struct battery_state *state)
{
    struct battery_info batteries;
    battery_info(&batteries);

    state->count     = batteries.count;
    state->ncharging = batteries.ncharging;
    state->ncharged  = batteries.ncharged;
}

int8_t battery_pct(void)
{
    return battery_life_percent();
}

int64_t battery_time(void)
{
    return battery_life_time();
}
