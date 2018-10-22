#ifndef GLUG_POWER_PLAT_H
#define GLUG_POWER_PLAT_H

#include <stdint.h>
#include <stddef.h>

struct battery_list;

int                 GLUG_LIB_LOCAL has_ac(void);

struct battery_list GLUG_LIB_LOCAL battery_list(void);
size_t              GLUG_LIB_LOCAL battery_count(void);
size_t              GLUG_LIB_LOCAL batteries_charging(const struct battery_list *list);
size_t              GLUG_LIB_LOCAL batteries_charged (const struct battery_list *list);

int8_t              GLUG_LIB_LOCAL avg_battery_pct (const struct battery_list *list);
int64_t             GLUG_LIB_LOCAL max_battery_time(const struct battery_list *list);

#endif // GLUG_POWER_PLAT_H
