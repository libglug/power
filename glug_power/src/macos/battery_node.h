#ifndef GLUG_BATTERY_NODE_H
#define GLUG_BATTERY_NODE_H

#include <CoreFoundation/CoreFoundation.h>

struct battery_info_node {
    CFDictionaryRef info;
    struct battery_info_node *next;
};

struct battery_info_node GLUG_LIB_LOCAL *create_battery_node(CFDictionaryRef info);
void                     GLUG_LIB_LOCAL  free_battery_list(struct battery_info_node *);

#endif // GLUG_BATTERY_NODE_H
