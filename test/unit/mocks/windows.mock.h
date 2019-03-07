#include <CUnit/Mocks.h>

#include <stdint.h>

enum ac_flags
{
    AC_LINE_OFFLINE = 0,
    AC_LINE_ONLINE = 1
};

enum battery_flags
{
    BATTERY_FLAG_NORMAL = 0,
    BATTERY_FLAG_NO_BATTERY = 1 << 0,
    BATTERY_FLAG_CHARGING = 1 << 1,
    BATTERY_FLAG_UNKNOWN = (unsigned char)-1
};

typedef struct _SYSTEM_POWER_STATUS {
    int BatteryFlag;
    int ACLineStatus;
    int BatteryLifePercent;
    unsigned int BatteryLifeTime;
} SYSTEM_POWER_STATUS;

CU_MOCK_FCN(void, GetSystemPowerStatus(SYSTEM_POWER_STATUS *ps));
