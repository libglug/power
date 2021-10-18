#ifndef MOCK_POWER_BRIDGE_H
#define MOCK_POWER_BRIDGE_H

#include <stdint.h>
#include <stddef.h>

#include <glug/bool_t.h>

struct battery_state
{
    size_t count;
    size_t ncharging;
    size_t ncharged;
};

void        set_ac(glug_bool_t);
glug_bool_t has_ac(void);

void battery_count(size_t *);

void set_batteries(size_t);
void set_charging_batteries(size_t);
void set_charged_batteries(size_t);
void battery_state(struct battery_state *);

void    set_battery_level(int8_t);
int8_t  battery_level(void);

void    set_battery_time(int32_t);
int32_t battery_time(void);


#endif // MOCK_POWER_BRIDGE_H
