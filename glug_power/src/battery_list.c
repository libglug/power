#include "battery_list.h"
#include "battery_platform.h"

void free_battery_list(struct battery_list *list)
{
    if (list)
    {
        struct battery_info_node *node, *next;
        for (node = list->batteries; node; node = next)
        {
            next = node->next;
            free_node(node);
        }
    }
}
