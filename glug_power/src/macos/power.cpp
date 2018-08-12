#include <glug/power/power.h>
#include <glug/power/battery_status.h>
#include <glug/power/power_supply.h>

#include "scoped_cf.hpp"
#include <vector>

#include <IOKit/ps/IOPowerSources.h>
#include <IOKit/ps/IOPSKeys.h>

namespace glug
{

using battery_info = scoped_cf<CFDictionaryRef>;

static std::vector<battery_info> get_batteries()
{
    scoped_cf<CFTypeRef> info = IOPSCopyPowerSourcesInfo();
    scoped_cf<CFArrayRef> sources = IOPSCopyPowerSourcesList(info);

    std::vector<battery_info> batteries;
    for (CFIndex i = 0; i < CFArrayGetCount(sources); ++i)
    {
        CFDictionaryRef source = IOPSGetPowerSourceDescription(info, CFArrayGetValueAtIndex(sources, i));
        CFStringRef type = reinterpret_cast<CFStringRef>(CFDictionaryGetValue(source, CFSTR(kIOPSTypeKey)));
        if (type && !CFStringCompare(type, CFSTR(kIOPSInternalBatteryType), 0))
            batteries.emplace_back(reinterpret_cast<CFDictionaryRef>(CFRetain(source)));
    }

    return batteries;
}

static bool any_charging(std::vector<battery_info> &batteries)
{
    bool charging = false;
    for (battery_info &battery: batteries)
    {
        CFBooleanRef is_charging = reinterpret_cast<CFBooleanRef>(CFDictionaryGetValue(battery, CFSTR(kIOPSIsChargingKey)));
        if (is_charging)
            charging = charging || CFBooleanGetValue(is_charging);
    }

    return charging;
}

static bool all_charged(std::vector<battery_info> &batteries)
{
    bool charged = batteries.size() > 0;
    for (battery_info &battery: batteries)
    {
        CFBooleanRef is_charged = reinterpret_cast<CFBooleanRef>(CFDictionaryGetValue(battery, CFSTR(kIOPSIsChargedKey)));
        if (is_charged)
            charged = charged && CFBooleanGetValue(is_charged);
    }

    return charged;
}

power_supply power_state()
{
    scoped_cf<CFTypeRef> info = IOPSCopyPowerSourcesInfo();
    CFStringRef source = IOPSGetProvidingPowerSourceType(info);

    if (!CFStringCompare(source, CFSTR(kIOPMACPowerKey), 0))
        return ps_ac;
    else if (!CFStringCompare(source, CFSTR(kIOPMBatteryPowerKey), 0))
        return ps_battery;

    return ps_unknown;
}

battery_status battery_state()
{
    std::vector<battery_info> batteries = get_batteries();
    const bool has_ac = power_state() == ps_ac;
    const bool has_battery = batteries.size() > 0;

    if (all_charged(batteries) && has_ac)   return bs_charged;
    if (any_charging(batteries))            return bs_charging;
    if (has_battery && !has_ac)             return bs_discharging;
    if (has_ac)                             return bs_none;
    return bs_unknown;
}

char battery_pct()
{
    std::vector<battery_info> batteries = get_batteries();
    if (!batteries.size()) return -1;

    int tot_cap = 0;
    for (battery_info &battery: batteries)
    {
        CFNumberRef cap = reinterpret_cast<CFNumberRef>(CFDictionaryGetValue(battery, CFSTR(kIOPSCurrentCapacityKey)));
        CFNumberRef max_cap = reinterpret_cast<CFNumberRef>(CFDictionaryGetValue(battery, CFSTR(kIOPSMaxCapacityKey)));

        int capacity = 0;
        if (cap)
            CFNumberGetValue(cap, kCFNumberIntType, &capacity);

        int max_capacity = 0;
        if (max_cap)
            CFNumberGetValue(max_cap, kCFNumberIntType, &max_capacity);

        if (max_capacity > 0)
            tot_cap += capacity * 100 / max_capacity;
    }

    return static_cast<char>(tot_cap * 1.0 / batteries.size());
}

long long battery_time()
{
    CFTimeInterval time = IOPSGetTimeRemainingEstimate();
    if (time == kIOPSTimeRemainingUnlimited) time = kIOPSTimeRemainingUnknown;
    return static_cast<long long>(time);
}

} // namespace glug
