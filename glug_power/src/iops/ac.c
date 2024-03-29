#include "iops.h"

#include <CoreFoundation/CoreFoundation.h>
#include <IOKit/ps/IOPowerSources.h>
#include <IOKit/ps/IOPSKeys.h>

#include <glug/bool_t.h>

glug_bool_t ac_connected(void)
{
    const CFTypeRef info     = IOPSCopyPowerSourcesInfo();
    const CFStringRef source = IOPSGetProvidingPowerSourceType(info);
    glug_bool_t ac = !CFStringCompare(source, CFSTR(kIOPMACPowerKey), 0);

    CFRelease(info);
    return ac;
}
