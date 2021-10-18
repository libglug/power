#ifndef MOCK_SYSCTL_H
#define MOCK_SYSCTL_H

#include <stddef.h>

void set_acline(int, int);
void set_battery_units(int, int);
void set_battery_state(int, int);
void set_battery_life(int, int);
void set_battery_time(int, int);
void clear_sysctl();

int sysctlbyname(const char *, void *, size_t *, void *, size_t *);

#endif // MOCK_SYSCTL_H
