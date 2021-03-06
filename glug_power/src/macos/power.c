#include "../power_platform.h"
#include "../battery_platform.h"
#include "../battery_list.h"
#include <glug/power/battery_status.h>
#include <glug/power/power_supply.h>

#include <CoreFoundation/CoreFoundation.h>
#include <IOKit/ps/IOPowerSources.h>
#include <IOKit/ps/IOPSKeys.h>

struct battery_list battery_list(void)
{
    struct battery_list batt_list = { .batteries = NULL, .count = 0 };
    struct battery_info_node batteries, *current;
    const CFTypeRef info = IOPSCopyPowerSourcesInfo();
    const CFArrayRef sources = IOPSCopyPowerSourcesList(info);
    CFIndex i;

    batteries.next = NULL;
    current = &batteries;

    for (i = 0; i < CFArrayGetCount(sources); ++i)
    {
        CFDictionaryRef source = IOPSGetPowerSourceDescription(info, CFArrayGetValueAtIndex(sources, i));
        CFStringRef type = (CFStringRef)CFDictionaryGetValue(source, CFSTR(kIOPSTypeKey));
        if (type && !CFStringCompare(type, CFSTR(kIOPSInternalBatteryType), 0))
        {
            current = current->next = create_battery_node(source);
            ++batt_list.count;
        }
    }

    CFRelease(info);
    CFRelease(sources);

    batt_list.batteries = batteries.next;
    return batt_list;
}

