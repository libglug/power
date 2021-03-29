#ifndef GLUG_POWER_BRIDGE_H
#define GLUG_POWER_BRIDGE_H

#include <stdint.h>
#include <stddef.h>

#include <glug/bool.h>

struct battery_state;

GLUG_LIB_LOCAL glug_bool    has_ac(void);
GLUG_LIB_LOCAL void         battery_count(size_t *);
GLUG_LIB_LOCAL void         battery_state(struct battery_state *);

GLUG_LIB_LOCAL int8_t       battery_pct (void);
GLUG_LIB_LOCAL int64_t      battery_time(void);

#endif // GLUG_POWER_BRIDGE_H
