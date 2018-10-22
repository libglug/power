#include "battery_list.h"
#include "battery_platform.h"

void  GLUG_LIB_LOCAL free_battery_list(struct battery_list *list)
{
    if (list)
    {
        struct battery_info_node *battery = list->batteries;
        while(battery)
        {
            free_node(battery);
            battery = battery->next;
        }
    }
}
