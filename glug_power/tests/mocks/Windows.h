#ifndef MOCK_WINDOWS_H
#define MOCK_WINDOWS_H

#include <stdint.h>

#define AC_LINE_OFFLINE                 0x00
#define AC_LINE_ONLINE                  0x01
#define AC_LINE_BACKUP_POWER            0x02
#define AC_LINE_UNKNOWN                 0xFF

#define BATTERY_FLAG_HIGH               0x01
#define BATTERY_FLAG_LOW                0x02
#define BATTERY_FLAG_CRITICAL           0x04
#define BATTERY_FLAG_CHARGING           0x08
#define BATTERY_FLAG_NO_BATTERY         0x80
#define BATTERY_FLAG_UNKNOWN            0xFF

typedef struct
{
    int8_t  ACLineStatus;
    int8_t  BatteryFlag;
    int8_t  BatteryLifePercent;
    int32_t BatteryLifeTime;
} SYSTEM_POWER_STATUS;

void set_ac_status(int8_t);
void set_battery_flag(int8_t);
void set_battery_life(int8_t);
void set_battery_time(int32_t);

void GetSystemPowerStatus(SYSTEM_POWER_STATUS *);

#endif // MOCK_WINDOWS_H
