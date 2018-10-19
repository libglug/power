#ifndef GLUG_POWER_H
#define GLUG_POWER_H

#include <glug/import.h>

#include <glug/power/battery_status.h>
#include <glug/power/power_supply.h>

#include <stdint.h>

enum power_supply   GLUG_LIB_API    power_state();
enum battery_status GLUG_LIB_API    battery_state();
int8_t              GLUG_LIB_API    battery_pct();
int64_t             GLUG_LIB_API    battery_time();

#endif // GLUG_POWER_H
