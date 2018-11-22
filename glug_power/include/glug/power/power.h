#ifndef GLUG_POWER_H
#define GLUG_POWER_H

#include <glug/import.h>
#include <glug/extern.h>

#include <glug/power/battery_status.h>
#include <glug/power/power_supply.h>

#include <stdint.h>

GLUG_EXTERN_START

enum glug_power_supply   GLUG_LIB_API   glug_power_state();
enum glug_battery_status GLUG_LIB_API   glug_battery_state();
int8_t                   GLUG_LIB_API   glug_battery_pct();
int64_t                  GLUG_LIB_API   glug_battery_time();

GLUG_EXTERN_END

#endif // GLUG_POWER_H
