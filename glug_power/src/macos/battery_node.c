#include "../battery_platform.h"

#include <string.h>
#include <stdlib.h>

#include <CoreFoundation/CoreFoundation.h>

struct battery_info_node GLUG_LIB_LOCAL *create_battery_node(const void *info)
{
    struct battery_info_node *battery = malloc(sizeof(struct battery_info_node));
    CFRetain(info);
    battery->info = info;
    battery->next = NULL;

    return battery;
}

void GLUG_LIB_LOCAL free_node(struct battery_info_node *battery)
{
    if (battery)
    {
        CFRelease(battery->info);
        free(battery);
    }
}
