#ifndef GLUG_POWER_BRIDGE_H
#define GLUG_POWER_BRIDGE_H

#include <stdint.h>
#include <stddef.h>

#include <glug/bool_t.h>

struct battery_state;

GLUG_LIB_LOCAL glug_bool_t  has_ac(void);
GLUG_LIB_LOCAL void         battery_count(size_t *);
GLUG_LIB_LOCAL void         battery_state(struct battery_state *);

GLUG_LIB_LOCAL int8_t       battery_level(void);
GLUG_LIB_LOCAL int32_t      battery_time (void);

#endif // GLUG_POWER_BRIDGE_H
