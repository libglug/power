#ifndef GLUG_BATTERY_LIST_H
#define GLUG_BATTERY_LIST_H

#include <stddef.h>

struct battery_list
{
    size_t count;
    struct battery_info_node *batteries;
};

GLUG_LIB_LOCAL void free_battery_list(struct battery_list *list);

#endif // GLUG_BATTERY_LIST_H
