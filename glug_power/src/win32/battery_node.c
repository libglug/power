#include "../battery_platform.h"

#include <string.h>
#include <stdlib.h>

GLUG_LIB_LOCAL struct battery_info_node *create_battery_node(const void *info)
{
    (void) info;
    return NULL;
}

GLUG_LIB_LOCAL void free_node(struct battery_info_node *battery)
{
    (void) battery;
}
