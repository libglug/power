#ifndef MOCK_SYSTEM_POWER_STATUS_H
#define MOCK_SYSTEM_POWER_STATUS_H

#include <stdint.h>

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

void               set_ac_line_status(enum ac_line_state state);
enum ac_line_state ac_line_status(void);

void               set_battery_flag(enum battery_flag flags);
enum battery_flag  battery_flag(void);

void   set_battery_percent(int8_t pct);
int8_t battery_life_percent(void);

void    set_battery_time(int32_t time);
int32_t battery_life_time(void);

#endif // MOCK_SYSTEM_POWER_STATUS_H
