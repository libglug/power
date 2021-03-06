#ifndef GLUG_POWER_H
#define GLUG_POWER_H

#include <glug/import.h>
#include <glug/extern.h>

#include <glug/power/battery_status.h>
#include <glug/power/power_supply.h>

#include <stdint.h>

GLUG_EXTERN_START

GLUG_LIB_API enum glug_power_supply   glug_power_active_supply(void);
GLUG_LIB_API enum glug_battery_status glug_power_battery_state(void);
GLUG_LIB_API int8_t                   glug_power_battery_pct(void);
GLUG_LIB_API int64_t                  glug_power_battery_time(void);

GLUG_EXTERN_END

#endif // GLUG_POWER_H
