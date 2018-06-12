#ifndef GLUG_POWER_H
#define GLUG_POWER_H

#include <glug/power/battery_status.h>
#include <glug/power/power_supply.h>

#include <glug/extern.h>
#include <glug/import.h>
#include <glug/namespace.h>

GLUG_NAMESPACE_START(glug)

GLUG_EXTERN_START

enum power_supply   GLUG_LIB_API    power_state();
enum battery_status GLUG_LIB_API    battery_state();
char                GLUG_LIB_API    battery_pct();
long long           GLUG_LIB_API    battery_time();

GLUG_EXTERN_END

GLUG_NAMESPACE_END

#endif // GLUG_POWER_H
