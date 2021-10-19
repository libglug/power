#ifndef GLUG_POWER_BATTERY_STATUS_HPP
#define GLUG_POWER_BATTERY_STATUS_HPP

namespace glug
{

namespace power
{

namespace priv
{
#include <glug/power/battery_status.h>
} // namespace priv

namespace battery
{
    enum status
    {
        unknown     = priv::glug_battery_unknown,
        none        = priv::glug_battery_none,
        discharging = priv::glug_battery_discharging,
        charging    = priv::glug_battery_charging,
        charged     = priv::glug_battery_charged,
    };
} // namespace battery

} // namespace power

} // namespace glug

#endif // GLUG_POWER_BATTERY_STATUS_HPP
