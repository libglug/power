#include "iops.h"

#include <CoreFoundation/CoreFoundation.h>
#include <IOKit/ps/IOPowerSources.h>
#include <IOKit/ps/IOPSKeys.h>

#include "../battery_list.h"
#include "../battery_platform.h"

int ac_connected(void)
{
    const CFTypeRef info = IOPSCopyPowerSourcesInfo();
    const CFStringRef source = IOPSGetProvidingPowerSourceType(info);
    int ac = CFStringCompare(source, CFSTR(kIOPMACPowerKey), 0) == 0;

    CFRelease(info);
    return ac;
}

size_t batteries_count(void)
{
    const CFTypeRef info = IOPSCopyPowerSourcesInfo();
    const CFArrayRef sources = IOPSCopyPowerSourcesList(info);
    size_t count = (size_t)CFArrayGetCount(sources);

    CFRelease(sources);
    CFRelease(info);
    return count;
}

size_t ncharging(const struct battery_list *batt_list)
{
    size_t is_charging = 0;
    const struct battery_info_node *current;

    if (!batt_list) return is_charging;

    for (current = batt_list->batteries; current; current = current->next)
    {
        CFBooleanRef bat_charging = CFDictionaryGetValue(current->info, CFSTR(kIOPSIsChargingKey));
        if (bat_charging && CFBooleanGetValue(bat_charging))
            ++is_charging;
    }

    return is_charging;
}

size_t ncharged(const struct battery_list *batt_list)
{
    size_t is_charged = 0;
    const struct battery_info_node *current;

    if (!batt_list) return is_charged;

    for (current = batt_list->batteries; current; current = current->next)
    {
        CFBooleanRef bat_charged = CFDictionaryGetValue(current->info, CFSTR(kIOPSIsChargedKey));
        if (bat_charged && CFBooleanGetValue(bat_charged))
            ++is_charged;
    }

    return is_charged;
}

uint8_t battery_life_percent(const struct battery_list *batt_list)
{
    int64_t total_cap = 0;
    struct battery_info_node *current;

    if (!batt_list || !batt_list->count) return (int8_t)-1;

    for (current = batt_list->batteries; current; current = current->next)
    {
        CFNumberRef cap = CFDictionaryGetValue(current->info, CFSTR(kIOPSCurrentCapacityKey));
        CFNumberRef max_cap = CFDictionaryGetValue(current->info, CFSTR(kIOPSMaxCapacityKey));
        int capacity = 0, max_capacity = 0;

        if (cap && max_cap)
        {
            CFNumberGetValue(cap, kCFNumberIntType, &capacity);
            CFNumberGetValue(max_cap, kCFNumberIntType, &max_capacity);
        }

        if (max_capacity > 0)
            total_cap += capacity * 100 / max_capacity;
    }

    return (int8_t)(total_cap * 1.0 / batt_list->count);
}

uint32_t battery_life_time(const struct battery_list *batt_list)
{
    CFTimeInterval time = IOPSGetTimeRemainingEstimate();
    (void) batt_list;
    if ((int)time == (int)kIOPSTimeRemainingUnlimited)
        time = kIOPSTimeRemainingUnknown;

    return (int64_t)time;
}
