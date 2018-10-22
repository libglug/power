#include "../battery_platform.h"

#include <string.h>
#include <stdlib.h>

struct battery_info_node GLUG_LIB_LOCAL *create_battery_node(const void *info)
{
    (void) info;
    return NULL;
}

void GLUG_LIB_LOCAL free_node(struct battery_info_node *battery)
{
    (void) battery;
}
