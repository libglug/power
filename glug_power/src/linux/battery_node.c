#include "../battery_platform.h"

#include <string.h>
#include <stdlib.h>

struct battery_info_node GLUG_LIB_LOCAL *create_battery_node(const void *name)
{
    struct battery_info_node *battery = malloc(sizeof(struct battery_info_node));
    battery->info = malloc(strlen(name) + 1);
    strcpy(battery->info, name);
    battery->next = NULL;

    return battery;
}

void GLUG_LIB_LOCAL free_node(struct battery_info_node *battery)
{
    if (battery)
    {
        free(battery->info);
        free(battery);
    }
}
