#include "sysctl.h"

#include <stddef.h>
#include <sys/sysctl.h>

glug_bool_t ac_connected(void)
{
    glug_bool_t acline = 0;
    size_t aclinesz = sizeof(acline);

    sysctlbyname("hw.acpi.acline", &acline, &aclinesz, NULL, 0);

    return acline;
}
