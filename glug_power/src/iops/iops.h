#ifndef GLUG_IOPS_H
#define GLUG_IOPS_H

#include <stdint.h>
#include <stddef.h>

#include <glug/bool_t.h>

enum power_source_type
{
    iops_unknown,
    iops_ac,
    iops_battery,
    iops_ups
};

struct battery;

struct battery_info
{
    size_t count;
    size_t ncharging;
    size_t ncharged;
};

GLUG_LIB_LOCAL enum power_source_type providing_power_source_type(void);

GLUG_LIB_LOCAL void iterate_batteries(void (*)(const struct battery *, void *), void *);

GLUG_LIB_LOCAL int32_t     battery_capacity(const struct battery *);
GLUG_LIB_LOCAL int32_t     battery_max_capacity(const struct battery *);
GLUG_LIB_LOCAL glug_bool_t battery_is_charged(const struct battery *);
GLUG_LIB_LOCAL glug_bool_t battery_is_charging(const struct battery *);
GLUG_LIB_LOCAL int32_t     battery_time_to_empty(const struct battery *);

#endif // GLUG_IOPS_H
