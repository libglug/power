#ifndef GLUG_BATTERY_STATUS_H
#define GLUG_BATTERY_STATUS_H

#include <glug/namespace.h>

GLUG_NAMESPACE_START(glug)

enum battery_status
{
    bs_unknown,
    bs_none,
    bs_discharging,
    bs_charging,
    bs_charged,
};

GLUG_NAMESPACE_END

#endif // GLUG_BATTERY_STATUS_H
