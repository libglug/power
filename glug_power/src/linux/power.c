#include "../power_platform.h"
#include "../battery_platform.h"
#include "../battery_list.h"
#include <glug/power/battery_status.h>
#include <glug/power/power_supply.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

static const char *power_root        = "/sys/class/power_supply";
static const char *batt_prefix       = "BAT";

struct battery_list battery_list(void)
{
    struct battery_list batt_list = { .batteries = NULL, .count = 0 };
    struct battery_info_node batteries, *current;
    struct dirent *ent;
    DIR *power_dir = opendir(power_root);

    batteries.next = NULL;
    current = &batteries;

    for(; power_dir && (ent = readdir(power_dir));)
        if (strstr(ent->d_name, batt_prefix) == ent->d_name)
        {
            current = current->next = create_battery_node(ent->d_name);
            ++batt_list.count;
        }

    closedir(power_dir);

    batt_list.batteries = batteries.next;
    return batt_list;
}
