#include "../battery_platform.h"

#include <string.h>
#include <stdlib.h>

struct battery_info_node *create_battery_node(const void *name)
{
    struct battery_info_node *battery = malloc(sizeof(struct battery_info_node));
    battery->info = strdup(name);
    battery->next = NULL;

    return battery;
}

void free_node(struct battery_info_node *battery)
{
    if (battery)
    {
        free(battery->info);
        free(battery);
    }
}
