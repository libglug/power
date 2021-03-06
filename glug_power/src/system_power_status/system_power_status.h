#ifndef GLUG_SYSTEM_POWER_STATUS_H
#define GLUG_SYSTEM_POWER_STATUS_H

#include <stdint.h>

#include <glug/bool.h>

GLUG_LIB_LOCAL glug_bool ac_connected(void);
GLUG_LIB_LOCAL glug_bool battery_connected(void);

GLUG_LIB_LOCAL glug_bool battery_charging(void);
GLUG_LIB_LOCAL glug_bool battery_charged(void);

GLUG_LIB_LOCAL uint8_t   battery_life_percent(void);
GLUG_LIB_LOCAL uint32_t  battery_life_time(void);

#endif // GLUG_SYSTEM_POWER_STATUS_H
