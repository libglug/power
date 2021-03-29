#include "sysfs.h"

#include <stdio.h>

static const char *ac_online_file = "/sys/class/power_supply/ACAD/online";

glug_bool ac_connected(void)
{
    long val = -1;
    FILE *fonline = fopen(ac_online_file, "r");

    if (fonline)
    {
        fscanf(fonline, "%ld", &val);
        fclose(fonline);
    }

    return val > 0;
}
