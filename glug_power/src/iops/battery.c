#include "iops.h"

#include <CoreFoundation/CoreFoundation.h>
#include <IOKit/ps/IOPowerSources.h>
#include <IOKit/ps/IOPSKeys.h>

static void iterate_batteries(void (*callback)(const CFDictionaryRef, void *), void *context)
{

    const CFTypeRef info     = IOPSCopyPowerSourcesInfo();
    const CFArrayRef sources = IOPSCopyPowerSourcesList(info);

    for (CFIndex i = 0; i < CFArrayGetCount(sources); ++i)
    {
        CFDictionaryRef source = IOPSGetPowerSourceDescription(info, CFArrayGetValueAtIndex(sources, i));
        CFStringRef type = CFDictionaryGetValue(source, CFSTR(kIOPSTypeKey));
        if (type && !CFStringCompare(type, CFSTR(kIOPSInternalBatteryType), 0))
            callback(source, context);
    }

    CFRelease(sources);
    CFRelease(info);
}

static void get_charge_state(const CFDictionaryRef source, void *context)
{
    struct battery_info *batinfo = context;

    ++batinfo->count;

    CFBooleanRef bat_charging = CFDictionaryGetValue(source, CFSTR(kIOPSIsChargingKey));
    if (bat_charging && CFBooleanGetValue(bat_charging))
        ++batinfo->ncharging;
    else
    {
        CFBooleanRef bat_charged = CFDictionaryGetValue(source, CFSTR(kIOPSIsChargedKey));
        if (bat_charged && CFBooleanGetValue(bat_charged))
            ++batinfo->ncharged;
    }
}

void battery_info(struct battery_info *batinfo)
{
    batinfo->count = 0;
    batinfo->ncharged = 0;
    batinfo->ncharging = 0;

    iterate_batteries(get_charge_state, batinfo);
}

struct battery_life
{
    int64_t total_capacity;
    size_t  nbats;
};

static void get_battery_life(const CFDictionaryRef source, void *context)
{
    struct battery_life *batt_life = context;

    CFNumberRef cap     = CFDictionaryGetValue(source, CFSTR(kIOPSCurrentCapacityKey));
    CFNumberRef max_cap = CFDictionaryGetValue(source, CFSTR(kIOPSMaxCapacityKey));

    if (cap && max_cap)
    {
        int32_t capacity = 0, max_capacity = 0;
        CFNumberGetValue(cap, kCFNumberSInt32Type, &capacity);
        CFNumberGetValue(max_cap, kCFNumberSInt32Type, &max_capacity);

        if (max_capacity > 0)
            batt_life->total_capacity += capacity * 100 / max_capacity;

        ++batt_life->nbats;
    }
}

int8_t battery_life_percent(void)
{
    struct battery_life batt_life = { 0, 0 };
    iterate_batteries(get_battery_life, &batt_life);

    if (batt_life.nbats) return (int8_t)(batt_life.total_capacity * 1.0 / batt_life.nbats);
    return (int8_t)-1;
}

static void get_battery_time(const CFDictionaryRef source, void *context)
{
    int32_t *remaining = context;

    CFBooleanRef bat_charging = CFDictionaryGetValue(source, CFSTR(kIOPSIsChargingKey));
    CFNumberRef time_ref      = CFDictionaryGetValue(source, CFSTR(kIOPSTimeToEmptyKey));

    if (bat_charging && CFBooleanGetValue(bat_charging)) return;

    if (time_ref)
    {
        int32_t source_time;
        CFNumberGetValue(time_ref, kCFNumberSInt32Type, &source_time);

        if (source_time >= 0)
        {
            source_time *= 60;
            *remaining = *remaining > source_time ? *remaining : source_time;
        }
    }
}

int32_t battery_life_time(void)
{
    int32_t time_remaining = -1;
    iterate_batteries(get_battery_life, &time_remaining);

    return time_remaining;
}
