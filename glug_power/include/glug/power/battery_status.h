#ifndef GLUG_BATTERY_STATUS_H
#define GLUG_BATTERY_STATUS_H

enum glug_battery_status
{
    glug_battery_unknown = -1,
    glug_battery_none,
    glug_battery_discharging,
    glug_battery_charging,
    glug_battery_charged,
};

#ifdef GLUG_USE_TYPEDEFS
    typedef enum glug_battery_status glug_battery_status_t;
#endif

#endif // GLUG_BATTERY_STATUS_H
