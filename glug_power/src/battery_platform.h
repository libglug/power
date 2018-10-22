#ifndef GLUG_BATTERY_PLAT_H
#define GLUG_BATTERY_PLAT_H

struct battery_info_node
{
    void *info;
    struct battery_info_node *next;
};

struct battery_info_node GLUG_LIB_LOCAL *create_battery_node(const void *info);
void                     GLUG_LIB_LOCAL  free_node(struct battery_info_node *battery);

#endif // GLUG_BATTERY_PLAT_H
