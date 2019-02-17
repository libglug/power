#ifndef GLUG_BATTERY_PLAT_H
#define GLUG_BATTERY_PLAT_H

struct battery_info_node
{
    void *info;
    struct battery_info_node *next;
};

GLUG_LIB_LOCAL struct battery_info_node * create_battery_node(const void *info);
GLUG_LIB_LOCAL void                       free_node(struct battery_info_node *battery);

#endif // GLUG_BATTERY_PLAT_H
