#include "iops.h"

#include <CoreFoundation/CoreFoundation.h>
#include <IOKit/ps/IOPowerSources.h>
#include <IOKit/ps/IOPSKeys.h>

#include <glug/bool_t.h>

struct battery
{
    CFDictionaryRef iops_battery_source;
};

enum power_source_type providing_power_source_type(void)
{
    const CFTypeRef info     = IOPSCopyPowerSourcesInfo();
    const CFStringRef source = IOPSGetProvidingPowerSourceType(info);

    enum power_source_type source_type = iops_unknown;
    if (!CFStringCompare(source, CFSTR(kIOPMACPowerKey), 0))      source_type = iops_ac;
    if (!CFStringCompare(source, CFSTR(kIOPMBatteryPowerKey), 0)) source_type = iops_battery;
    if (!CFStringCompare(source, CFSTR(kIOPMUPSPowerKey), 0))     source_type = iops_ups;

    CFRelease(info);
    return source_type;
}

void iterate_batteries(void (*callback)(const struct battery *, void *), void *context)
{

    const CFTypeRef info     = IOPSCopyPowerSourcesInfo();
    const CFArrayRef sources = IOPSCopyPowerSourcesList(info);

    for (CFIndex i = 0; i < CFArrayGetCount(sources); ++i)
    {
        CFDictionaryRef source = IOPSGetPowerSourceDescription(info, CFArrayGetValueAtIndex(sources, i));
        CFStringRef type = CFDictionaryGetValue(source, CFSTR(kIOPSTypeKey));
        if (type && !CFStringCompare(type, CFSTR(kIOPSInternalBatteryType), 0))
        {
            struct battery battery = (struct battery){ .iops_battery_source = source };
            callback(&battery, context);
        }
    }

    CFRelease(sources);
    CFRelease(info);
}

int32_t battery_capacity(const struct battery *source)
{
    CFNumberRef cap_ref = CFDictionaryGetValue(source->iops_battery_source, CFSTR(kIOPSCurrentCapacityKey));

    int32_t capacity;
    CFNumberGetValue(cap_ref, kCFNumberSInt32Type, &capacity);

    return capacity;
}


int32_t battery_max_capacity(const struct battery *source)
{
    CFNumberRef maxcap_ref = CFDictionaryGetValue(source->iops_battery_source, CFSTR(kIOPSMaxCapacityKey));

    int32_t max_capacity;
    CFNumberGetValue(maxcap_ref, kCFNumberSInt32Type, &max_capacity);

    return max_capacity;
}

glug_bool_t battery_is_charged(const struct battery *source)
{
    CFBooleanRef charged_ref = CFDictionaryGetValue(source->iops_battery_source, CFSTR(kIOPSIsChargedKey));

    return charged_ref && CFBooleanGetValue(charged_ref);
}

glug_bool_t battery_is_charging(const struct battery *source)
{
    CFBooleanRef charging_ref = CFDictionaryGetValue(source->iops_battery_source, CFSTR(kIOPSIsChargingKey));

    return charging_ref && CFBooleanGetValue(charging_ref);
}

int32_t battery_time_to_empty(const struct battery *source)
{

    CFNumberRef time_ref = CFDictionaryGetValue(source->iops_battery_source, CFSTR(kIOPSTimeToEmptyKey));
    if (!time_ref) return -1;

    int32_t time;
    CFNumberGetValue(time_ref, kCFNumberSInt32Type, &time);

    return time;
}
