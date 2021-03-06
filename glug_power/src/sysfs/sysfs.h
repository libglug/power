#ifndef GLUG_SYSFS_H
#define GLUG_SYSFS_H

#include <stdint.h>
#include <stddef.h>

#include <glug/bool.h>

struct battery_list;

GLUG_LIB_LOCAL glug_bool ac_connected(void);
GLUG_LIB_LOCAL size_t    batteries_count(void);

GLUG_LIB_LOCAL size_t    ncharging(const struct battery_list *);
GLUG_LIB_LOCAL size_t    ncharged(const struct battery_list *);

GLUG_LIB_LOCAL uint8_t   battery_life_percent(const struct battery_list *);
GLUG_LIB_LOCAL uint32_t  battery_life_time(const struct battery_list *);

#endif // GLUG_SYSFS_H
