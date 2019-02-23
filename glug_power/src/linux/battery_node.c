#include "../battery_platform.h"

#include <string.h>
#include <stdlib.h>

GLUG_LIB_LOCAL struct battery_info_node *create_battery_node(const void *name)
{
    struct battery_info_node *battery = malloc(sizeof(struct battery_info_node));
    battery->info = malloc(strlen(name) + 1);
    strcpy(battery->info, name);
    battery->next = NULL;

    return battery;
}

GLUG_LIB_LOCAL void free_node(struct battery_info_node *battery)
{
    if (battery)
    {
        free(battery->info);
        free(battery);
    }
}
