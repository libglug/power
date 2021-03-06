#ifndef GLUG_POWER_SUPPLY_H
#define GLUG_POWER_SUPPLY_H

enum glug_power_supply
{
    glug_power_unknown = -1,
    glug_power_none,
    glug_power_ac,
    glug_power_battery,
    glug_power_ups
};

#ifdef GLUG_USE_TYPEDEFS
    typedef enum glug_power_supply glug_power_supply_t;
#endif

#endif // GLUG_POWER_SUPPLY_H
