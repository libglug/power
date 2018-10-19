#include <glug/power/power.h>

#include <stdio.h>

int main()
{
    printf("power supply: %d\n", power_state());
    printf("battery state: %d\n", battery_state());
    printf("battery %%: %d\n", battery_pct());

    const long long time = battery_time();
    printf("time left: %lld:%02lld:%02lld\n", time / 60 / 60, time / 60 % 60, time % 60);
}
