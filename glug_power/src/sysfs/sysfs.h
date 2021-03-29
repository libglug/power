#ifndef GLUG_SYSFS_H
#define GLUG_SYSFS_H

#include <stdint.h>
#include <stddef.h>

#include <glug/bool.h>

struct battery_list;

struct battery_info
{
    size_t count;
    size_t ncharging;
    size_t ncharged;
};

GLUG_LIB_LOCAL glug_bool ac_connected(void);
GLUG_LIB_LOCAL void      battery_info(struct battery_info *);

GLUG_LIB_LOCAL int8_t   battery_life_percent(void);
GLUG_LIB_LOCAL int32_t  battery_life_time(void);

#endif // GLUG_SYSFS_H
