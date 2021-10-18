#include "sysctl.h"

#include <string.h>

enum sysctl_keys
{
    acline,
    battery_units,
    battery_state,
    battery_life,
    battery_time,
    count,
};

struct info
{
    int available;
    int value;
    int size;
};

static struct info SYSCTL[count] = {
    { 1, 1, sizeof(int) },
    { 0, 0, sizeof(int)  },
    { 0, 0, sizeof(int)  },
    { 0, 0, sizeof(int)  },
    { 0, 0, sizeof(int)  },
};

static int index_from_name(const char *name)
{
    if (!strcmp(name, "hw.acpi.acline")) return acline;
    if (!strcmp(name, "hw.acpi.battery.units")) return battery_units;
    if (!strcmp(name, "hw.acpi.battery.state")) return battery_state;
    if (!strcmp(name, "hw.acpi.battery.life")) return battery_life;
    if (!strcmp(name, "hw.acpi.battery.time")) return battery_time;

    return -1;
}

void clear_sysctl()
{
    SYSCTL[0] = (struct info){ 1, 1, sizeof(int) };
    SYSCTL[1] = (struct info){ 0, 0, sizeof(int) };
    SYSCTL[2] = (struct info){ 0, 0, sizeof(int) };
    SYSCTL[3] = (struct info){ 0, 0, sizeof(int) };
    SYSCTL[4] = (struct info){ 0, 0, sizeof(int) };
}

void set_acline(int available, int value)
{
    SYSCTL[acline].available = available;
    SYSCTL[acline].value = value;
}

void set_battery_units(int available, int value)
{
    SYSCTL[battery_units].available = available;
    SYSCTL[battery_units].value = value;
}

void set_battery_state(int available, int value)
{
    SYSCTL[battery_state].available = available;
    SYSCTL[battery_state].value = value;
}

void set_battery_life(int available, int value)
{
    SYSCTL[battery_life].available = available;
    SYSCTL[battery_life].value = value;
}

void set_battery_time(int available, int value)
{
    SYSCTL[battery_time].available = available;
    SYSCTL[battery_time].value = value;
}

int sysctlbyname(const char *name, void *oldp, size_t *oldlen, void *newp, size_t *newlen)
{
    int index = index_from_name(name);

    if (index == -1 || !SYSCTL[index].available) return -1;

    struct info info = SYSCTL[index];
    memcpy(oldp, &info.value, *oldlen);
    *oldlen = info.size;

    return 0;
}
