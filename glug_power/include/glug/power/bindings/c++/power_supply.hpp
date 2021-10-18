#ifndef GLUG_POWER_SUPPLY_HPP
#define GLUG_POWER_SUPPLY_HPP

namespace glug
{

namespace power
{

namespace priv
{
#include <glug/power/power_supply.h>
} // namespace priv

struct supply
{
    enum type
    {
        unknown = priv::glug_power_unknown,
        none    = priv::glug_power_none,
        ac      = priv::glug_power_ac,
        battery = priv::glug_power_battery,
        ups     = priv::glug_power_ups,
    };
};


} // namespace power

} // namespace glug

#endif // GLUG_POWER_SUPPLY_HPP
