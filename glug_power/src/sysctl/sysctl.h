#ifndef GLUG_SYS_SYSCTL_H
#define GLUG_SYS_SYSCTL_H

#include <stdint.h>

#include <glug/bool_t.h>

enum charge_state
{
    cs_unknown = -1,
    cs_none,
    cs_discharging,
    cs_charging,
    cs_charged,
};

GLUG_LIB_LOCAL glug_bool_t ac_connected(void);
GLUG_LIB_LOCAL glug_bool_t battery_connected(void);

GLUG_LIB_LOCAL enum charge_state battery_charge_state(void);
GLUG_LIB_LOCAL int8_t   battery_life_percent(void);
GLUG_LIB_LOCAL int32_t  battery_life_time(void);

#endif // GLUG_SYS_SYSCTL_H
