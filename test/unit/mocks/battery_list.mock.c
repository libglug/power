#include "battery_list.mock.h"
#include <glug/power/battery_status.h>

#include <stdlib.h>

struct battery_list
{
    size_t count;
    struct battery_info_node *batteries;
};

static size_t charged_batteries = 0;
static size_t charging_batteries = 0;
static size_t unknown_batteries = 0;

static struct battery_list batt_list = { 0 };

void build_battery_list_none()
{
    batt_list.count = 0;
}

void build_battery_list_charged()
{
    batt_list.count = 3;
    charged_batteries = 3;
}

void build_battery_list_charging()
{
    batt_list.count = 2;
    charging_batteries = 2;
}

void build_battery_list_unknown()
{
    batt_list.count = 1;
    unknown_batteries = 1;
}

void build_battery_list_mixed()
{
    batt_list.count = 4;
    charging_batteries = 1;
    charged_batteries = 1;
    unknown_batteries = 2;
}

struct battery_list battery_list(void)
{
    return batt_list;
}

size_t battery_count(void)
{
    return batt_list.count;
}

void free_battery_list(struct battery_list *list)
{
    (void) list;
}

size_t batteries_charging(const struct battery_list *list)
{
    (void) list;
    return charging_batteries;
}

size_t batteries_charged(const struct battery_list *list)
{
    (void) list;
    return charged_batteries;
}


int8_t mock_pct()
{
    return 75;
}

int8_t avg_battery_pct(const struct battery_list *list)
{
    (void) list;
    return mock_pct();
}

int mock_hours()
{
    return 2;
}

int mock_minutes()
{
    return 14;
}

int mock_seconds()
{
    return 51;
}

int64_t max_battery_time(const struct battery_list *list)
{
    (void) list;
    return mock_hours() * 60 * 60 + mock_minutes() * 60 + mock_seconds();
}

