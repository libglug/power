#include "sysctl.h"

#include <stddef.h>
#include <sys/sysctl.h>

glug_bool_t battery_connected(void)
{
    size_t nbatts = 0;
    size_t nbattssz = sizeof(nbatts);

    sysctlbyname("hw.acpi.battery.units", &nbatts, &nbattssz, NULL, 0);

    return nbatts > 0;
}

enum charge_state battery_charge_state(void)
{
    size_t nbatts = 0;
    size_t nbattssz = sizeof(nbatts);
    int32_t batt_state = 0;
    size_t statesz = sizeof(batt_state);

    int batt_status  = sysctlbyname("hw.acpi.battery.units", &nbatts, &nbattssz, NULL, 0);
    int state_status = sysctlbyname("hw.acpi.battery.state", &batt_state, &statesz, NULL, 0);

    if (batt_status == -1 || state_status == -1 || batt_state == -1) return cs_unknown;

    return (batt_state == 0) * cs_charged +
           (batt_state == 1) * cs_discharging +
           (batt_state == 2) * cs_charging;
}

int8_t battery_life_percent(void)
{
    int8_t batt_life = -1;
    size_t lifesz = sizeof(batt_life);

    sysctlbyname("hw.acpi.battery.life", &batt_life, &lifesz, NULL, 0);

    return batt_life;
}

int32_t battery_life_time(void)
{
    int32_t batt_time = -1;
    size_t timesz = sizeof(batt_time);

    sysctlbyname("hw.acpi.battery.time", &batt_time, &timesz, NULL, 0);

    return (batt_time != -1) * (batt_time * 60) +
           (batt_time == -1) * batt_time;
}
