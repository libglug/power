#ifndef GLUG_SYSTEM_POWER_STATUS_H
#define GLUG_SYSTEM_POWER_STATUS_H

#include <stdint.h>

#include <glug/bool_t.h>

enum ac_line_state
{
    ac_unknown = -1,
    ac_offline,
    ac_online
};

enum battery_flag
{
    bf_high     = 1 << 0,
    bf_low      = 1 << 1,
    bf_critical = 1 << 2,
    bf_charging = 1 << 3,
    bf_none     = 1 << 7,
    bf_unknown  = (1 << 8) - 1,
};


GLUG_LIB_LOCAL enum ac_line_state ac_line_status(void);
GLUG_LIB_LOCAL enum battery_flag  battery_flag(void);
GLUG_LIB_LOCAL int8_t      battery_life_percent(void);
GLUG_LIB_LOCAL int32_t     battery_life_time(void);

#endif // GLUG_SYSTEM_POWER_STATUS_H
