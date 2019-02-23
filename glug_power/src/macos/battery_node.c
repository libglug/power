#include "../battery_platform.h"

#include <string.h>
#include <stdlib.h>

#include <CoreFoundation/CoreFoundation.h>

GLUG_LIB_LOCAL struct battery_info_node *create_battery_node(const void *info)
{
    struct battery_info_node *battery = malloc(sizeof(struct battery_info_node));
    battery->info = (void *)CFRetain(info);
    battery->next = NULL;

    return battery;
}

GLUG_LIB_LOCAL void free_node(struct battery_info_node *battery)
{
    if (battery)
    {
        CFRelease(battery->info);
        free(battery);
    }
}
