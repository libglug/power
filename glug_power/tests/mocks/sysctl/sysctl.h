#ifndef MOCK_GLUG_SYSCTL_H
#define MOCK_GLUG_SYSCTL_H

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

void set_ac_connected(glug_bool_t);
glug_bool_t ac_connected(void);

void set_battery_connected(glug_bool_t);
glug_bool_t battery_connected(void);

void set_charge_state(enum charge_state);
enum charge_state battery_charge_state(void);

void set_battery_life(int8_t);
int8_t   battery_life_percent(void);

void set_battery_time(int32_t);
int32_t  battery_life_time(void);

#endif // MOCK_GLUG_SYSCTL_H
