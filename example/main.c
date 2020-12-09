#include <glug/power/power.h>

#include <stdio.h>

int main()
{
    printf("power supply: %d\n", glug_power_active_supply());
    printf("battery state: %d\n", glug_power_battery_state());
    printf("battery %%: %d\n", glug_power_battery_pct());

    const long long time = glug_power_battery_time();
    printf("time left: %lld:%02lld:%02lld\n", time / 60 / 60, time / 60 % 60, time % 60);
}
