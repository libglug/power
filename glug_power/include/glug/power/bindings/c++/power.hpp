#ifndef GLUG_POWER_HPP
#define GLUG_POWER_HPP

#include <stdint.h>

#include <glug/power/bindings/c++/power_supply.hpp>
#include <glug/power/bindings/c++/battery_status.hpp>

namespace glug
{

namespace power
{

bool              has_ac();
supply::type      active_supply(void);
battery::status   battery_state(void);
int8_t            battery_level(void);
int32_t           battery_time(void);

} // namespace power

} // namespace glug

#include "power.inl"

#endif // GLUG_POWER_HPP
