#ifndef GLUG_BATTERY_NODE_H
#define GLUG_BATTERY_NODE_H

struct battery_name_node {
    char *name;
    struct battery_name_node *next;
};

struct battery_name_node GLUG_LIB_LOCAL *create_battery_node(const char *name);
void                     GLUG_LIB_LOCAL  free_battery_list(struct battery_name_node *);

#endif // GLUG_BATTERY_NODE_H
