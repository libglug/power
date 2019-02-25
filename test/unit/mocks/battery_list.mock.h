#include <stdint.h>

void build_battery_list_none(void);
void build_battery_list_charged(void);
void build_battery_list_charging(void);
void build_battery_list_unknown(void);
void build_battery_list_mixed(void);

int8_t mock_pct(void);

int mock_hours(void);
int mock_minutes(void);
int mock_seconds(void);
