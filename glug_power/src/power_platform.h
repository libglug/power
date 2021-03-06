#ifndef GLUG_POWER_PLAT_H
#define GLUG_POWER_PLAT_H

#include <stdint.h>
#include <stddef.h>

#include <glug/bool.h>

struct battery_list;

GLUG_LIB_LOCAL glug_bool           has_ac(void);

GLUG_LIB_LOCAL struct battery_list battery_list(void);
GLUG_LIB_LOCAL size_t              battery_count(void);
GLUG_LIB_LOCAL size_t              batteries_charging(const struct battery_list *list);
GLUG_LIB_LOCAL size_t              batteries_charged (const struct battery_list *list);

GLUG_LIB_LOCAL int8_t              avg_battery_pct (const struct battery_list *list);
GLUG_LIB_LOCAL int64_t             max_battery_time(const struct battery_list *list);

#endif // GLUG_POWER_PLAT_H
