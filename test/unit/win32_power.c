#include <glug/power.h>
#include <CUnit/Mocks.h>
#include <CUnit/Basic.h>
#include <CUnit/Assert.h>

#include "battery_list.h"
#include <power_platform.h>
#include "../create_suite.h"

#include CU_MOCK_INCLUDE("Windows.h", "mocks/windows.mock.h")

static int ac_status = AC_LINE_OFFLINE;
static enum battery_flags battery_status = BATTERY_FLAG_UNKNOWN;
static int avg_batt_pct = 100;
static int battery_time = 15151515;
void mock_GetSystemPowerStatus(SYSTEM_POWER_STATUS *ps)
{
    ps->ACLineStatus = ac_status;
    ps->BatteryFlag = battery_status;
    ps->BatteryLifePercent = avg_batt_pct;
    ps->BatteryLifeTime = battery_time;
}

void before_each(void)
{
    ac_status = AC_LINE_OFFLINE;
    battery_status = BATTERY_FLAG_NO_BATTERY;
    avg_batt_pct = 100;
    battery_time = 15151515;
}

void test_has_ac(void)
{
    CU_ASSERT_FALSE(has_ac());

    ac_status = 1;
    CU_ASSERT_TRUE(has_ac());
}

void test_battery_list(void)
{
    struct battery_list batteries = battery_list();
    CU_ASSERT_EQUAL(batteries.count, 0);

    battery_status = BATTERY_FLAG_CHARGING;
    batteries = battery_list();
    CU_ASSERT_EQUAL(batteries.count, 1)
}

void test_battery_count(void)
{
    CU_ASSERT_EQUAL(battery_count(), 0);

    battery_status = BATTERY_FLAG_CHARGING;
    CU_ASSERT_EQUAL(battery_count(), 1);
}

void test_batteries_charging(void)
{
    CU_ASSERT_EQUAL(batteries_charging(NULL), 0);

    battery_status = BATTERY_FLAG_CHARGING;
    CU_ASSERT_EQUAL(batteries_charging(NULL), 1);
}

void test_batteries_charged(void)
{
    // ac off, and unknown battery == no batteries charged
    CU_ASSERT_EQUAL(batteries_charged(NULL), 0);

    // ac on, and unknown battery == no batteries charged
    ac_status = AC_LINE_ONLINE;
    CU_ASSERT_EQUAL(batteries_charged(NULL), 0);

    // ac off, and normal battery == no batteries charged
    ac_status = AC_LINE_OFFLINE;
    battery_status = BATTERY_FLAG_NORMAL;
    CU_ASSERT_EQUAL(batteries_charged(NULL), 0);

    // ac on, and non-charging battery == batteries charged
    ac_status = AC_LINE_ONLINE;
    CU_ASSERT_EQUAL(batteries_charged(NULL), 1);
}

void test_battery_pct(void)
{
    int percent = avg_batt_pct;
    CU_ASSERT_EQUAL(avg_battery_pct(NULL), percent);

    percent = 24;
    avg_batt_pct = percent;
    CU_ASSERT_EQUAL(avg_battery_pct(NULL), percent);
}

void test_battery_time(void)
{
    int time = battery_time;
    CU_ASSERT_EQUAL(max_battery_time(NULL), time);

    time = -1;
    battery_time = time;
    CU_ASSERT_EQUAL(max_battery_time(NULL), time);
}

int main(void)
{
    int failures = 0;
    CU_pSuite suite = create_suite("battery stats", before_each, NULL);
    if (!suite) return CU_get_error();

    CU_add_test(suite, "has AC", test_has_ac);
    CU_add_test(suite, "battery list", test_battery_list);
    CU_add_test(suite, "battery count", test_battery_count);
    CU_add_test(suite, "# of batteries charging", test_batteries_charging);
    CU_add_test(suite, "# of batteries charged", test_batteries_charged);
    CU_add_test(suite, "battery %", test_battery_pct);
    CU_add_test(suite, "battery time", test_battery_time);

    failures = run_tests(CU_BRM_VERBOSE);
    CU_cleanup_registry();

    return failures;
}
