#include "power_bridge.h"

#include "battery_state_t.h"
#include <glug/bool_t.h>

glug_bool_t has_ac(void)
{
    return 0;
}

void battery_count(size_t *count)
{

}

void battery_state(struct battery_state *state)
{

}

int8_t battery_level()
{
    return -1;
}

int32_t battery_time()
{
    return -1;
}
