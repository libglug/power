#include "battery_node.h"

#include <string.h>
#include <stdlib.h>

struct battery_name_node GLUG_LIB_LOCAL *create_battery_node(const char *name)
{
    struct battery_name_node *battery = malloc(sizeof(struct battery_name_node));
    battery->name = malloc(strlen(name) + 1);
    strcpy(battery->name, name);
    battery->next = NULL;

    return battery;
}

void GLUG_LIB_LOCAL free_battery_list(struct battery_name_node *list)
{
    struct battery_name_node *current = list;
    while (current)
    {
        struct battery_name_node *next = current->next;
        free(current->name);
        free(current);
        current = next;
    }
}
