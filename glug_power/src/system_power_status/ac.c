#include "system_power_status.h"

#include <glug/bool_t.h>

#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

glug_bool_t ac_connected(void)
{
    SYSTEM_POWER_STATUS ps;
    GetSystemPowerStatus(&ps);

    return ps.ACLineStatus == AC_LINE_ONLINE;
}
