#ifndef GLUG_BATTERY_STATE_H
#define GLUG_BATTERY_STATE_H

#include <stddef.h>

struct battery_state
{
    size_t count;
    size_t ncharging;
    size_t ncharged;
};

#endif // GLUG_BATTERY_STATE_H
