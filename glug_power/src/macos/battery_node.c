#include "battery_node.h"

#include <string.h>
#include <stdlib.h>

struct battery_info_node GLUG_LIB_LOCAL *create_battery_node(CFDictionaryRef info)
{
    struct battery_info_node *battery = malloc(sizeof(struct battery_info_node));
    CFRetain(info);
    battery->info = info;
    battery->next = NULL;

    return battery;
}

void GLUG_LIB_LOCAL free_battery_list(struct battery_info_node *list)
{
    struct battery_info_node *current = list;
    while (current)
    {
        struct battery_info_node *next = current->next;
        CFRelease(current->info);
        free(current);
        current = next;
    }
}
