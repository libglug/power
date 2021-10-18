#include "power.hpp"

namespace glug
{

namespace power
{

namespace priv
{
#include <glug/power/power.h>
#include <glug/power/power_supply.h>
#include <glug/power/battery_status.h>
} //namespace priv

bool has_ac()
{
    return !!priv::glug_power_has_ac();
}

supply::type active_supply(void)
{
    return static_cast<supply::type>(priv::glug_power_active_supply());
}

battery::status battery_state(void)
{
    return static_cast<battery::status>(priv::glug_power_battery_state());
}

int8_t battery_level(void)
{
    return priv::glug_power_battery_level();
}

int32_t battery_time(void)
{
    return priv::glug_power_battery_time();
}

} // namespace power

} // namespace glug
