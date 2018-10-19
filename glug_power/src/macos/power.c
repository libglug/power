#include <glug/power/power.h>
#include <glug/power/battery_status.h>
#include <glug/power/power_supply.h>
#include "battery_node.h"

#include <CoreFoundation/CoreFoundation.h>
#include <IOKit/ps/IOPowerSources.h>
#include <IOKit/ps/IOPSKeys.h>

static struct battery_info_node *get_batteries(size_t *count)
{
    struct battery_info_node batteries, *current;
    const CFTypeRef info = IOPSCopyPowerSourcesInfo();
    const CFArrayRef sources = IOPSCopyPowerSourcesList(info);
    CFIndex i;
    size_t bat_count = 0;

    batteries.info = NULL;
    batteries.next = NULL;
    current = &batteries;

    for (i = 0; i < CFArrayGetCount(sources); ++i)
    {
        const CFDictionaryRef source = IOPSGetPowerSourceDescription(info, CFArrayGetValueAtIndex(sources, i));
        const CFStringRef type = (CFStringRef)CFDictionaryGetValue(source, CFSTR(kIOPSTypeKey));
        if (type && !CFStringCompare(type, CFSTR(kIOPSInternalBatteryType), 0))
        {
            current = current->next = create_battery_node(source);
            bat_count++;
        }
    }

    CFRelease(sources);
    CFRelease(info);

    if (count) *count = bat_count;
    return batteries.next;
}

static size_t batteries_charging(const struct battery_info_node *batteries)
{
    size_t is_charging = 0;
    const struct battery_info_node *current;

    for(current = batteries; !is_charging && current; current = current->next)
    {
        CFBooleanRef bat_charging = (CFBooleanRef)CFDictionaryGetValue(current->info, CFSTR(kIOPSIsChargingKey));
        if (bat_charging && CFBooleanGetValue(bat_charging))
            ++is_charging;
    }

    return is_charging;
}

static size_t batteries_charged(const struct battery_info_node *batteries)
{
    size_t is_charged = 0;
    const struct battery_info_node *current;

    for(current = batteries; is_charged && current; current = current->next)
    {
        CFBooleanRef bat_charged = (CFBooleanRef)CFDictionaryGetValue(current->info, CFSTR(kIOPSIsChargedKey));
        if (bat_charged && CFBooleanGetValue(bat_charged))
            ++is_charged;
    }

    return is_charged;
}

enum power_supply GLUG_LIB_API power_state()
{
    const CFTypeRef info = IOPSCopyPowerSourcesInfo();
    const CFStringRef source = IOPSGetProvidingPowerSourceType(info);
    enum power_supply power_state = ps_unknown;

    if (!CFStringCompare(source, CFSTR(kIOPMACPowerKey), 0))            power_state = ps_ac;
    else if (!CFStringCompare(source, CFSTR(kIOPMBatteryPowerKey), 0))  power_state = ps_battery;

    CFRelease(info);
    return power_state;
}

enum battery_status GLUG_LIB_API battery_state()
{
    size_t bat_count;
    struct battery_info_node *batteries = get_batteries(&bat_count);
    const int has_ac = power_state() == ps_ac;
    const int has_battery = batteries != NULL;
    enum battery_status battery_state = bs_unknown;

    if (batteries_charged(batteries) == bat_count) battery_state = bs_charged;
    else if (batteries_charging(batteries))              battery_state = bs_charging;
    else if (has_battery && !has_ac)                     battery_state = bs_discharging;
    else if (!has_battery && has_ac)                     battery_state = bs_none;

    free_battery_list(batteries);
    return battery_state;
}

int8_t GLUG_LIB_API battery_pct()
{
    int total_cap = 0;
    size_t bat_count = 0;
    struct battery_info_node *current, *batteries = get_batteries();

    for(current = batteries; current; current = current->next)
    {
        CFNumberRef cap = (CFNumberRef)CFDictionaryGetValue(current->info, CFSTR(kIOPSCurrentCapacityKey));
        CFNumberRef max_cap = (CFNumberRef)CFDictionaryGetValue(current->info, CFSTR(kIOPSMaxCapacityKey));
        int capacity = 0, max_capacity = 0;

        if (cap)
            CFNumberGetValue(cap, kCFNumberIntType, &capacity);
        if (max_cap)
            CFNumberGetValue(max_cap, kCFNumberIntType, &max_capacity);

        if (max_capacity > 0)
            total_cap += capacity * 100 / max_capacity;

        ++bat_count;
    }

    free_battery_list(batteries);
    if (!batteries) return -1;
    return (char)(total_cap * 1.0 / bat_count);
}

int64_t GLUG_LIB_API battery_time()
{
    CFTimeInterval time = IOPSGetTimeRemainingEstimate();
    if ((int)time == (int)kIOPSTimeRemainingUnlimited) time = kIOPSTimeRemainingUnknown;
    return (int64_t)time;
}
