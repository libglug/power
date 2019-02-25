#include <glug/power.h>
#include <CUnit/Basic.h>
#include <CUnit/Assert.h>

#include "mocks/ac.mock.h"
#include "mocks/battery_list.mock.h"
#include "create_suite.h"

void before_each(void)
{
    disable_ac();
}

void test_no_batteries(void)
{
    enable_ac();
    build_battery_list_none();
    CU_ASSERT_EQUAL(glug_power_state(), glug_ps_ac);
    CU_ASSERT_EQUAL(glug_battery_state(), glug_bs_none);
}

void test_unknown_battery_state(void)
{
    build_battery_list_none();
    CU_ASSERT_EQUAL(glug_power_state(), glug_ps_unknown);
    CU_ASSERT_EQUAL(glug_battery_state(), glug_bs_unknown);
}

void test_batteries_charged(void)
{
    enable_ac();
    build_battery_list_charged();
    CU_ASSERT_EQUAL(glug_power_state(), glug_ps_ac);
    CU_ASSERT_EQUAL(glug_battery_state(), glug_bs_charged);
}

void test_batteries_charging(void)
{
    enable_ac();
    build_battery_list_charging();
    CU_ASSERT_EQUAL(glug_power_state(), glug_ps_ac);
    CU_ASSERT_EQUAL(glug_battery_state(), glug_bs_charging);
}

void test_batteries_discharging(void)
{
    build_battery_list_charging();
    CU_ASSERT_EQUAL(glug_power_state(), glug_ps_battery);
    CU_ASSERT_EQUAL(glug_battery_state(), glug_bs_discharging);
}

void test_batteries_mixed_disc(void)
{
    build_battery_list_mixed();
    CU_ASSERT_EQUAL(glug_power_state(), glug_ps_battery);
    CU_ASSERT_EQUAL(glug_battery_state(), glug_bs_discharging);
}

void test_batteries_mixed_charging(void)
{
    enable_ac();
    build_battery_list_mixed();
    CU_ASSERT_EQUAL(glug_power_state(), glug_ps_ac);
    CU_ASSERT_EQUAL(glug_battery_state(), glug_bs_charging);
}

void test_batteries_pct_charged(void)
{
    CU_ASSERT_EQUAL(glug_battery_pct(), mock_pct());
}

void test_batteries_time(void)
{
    int64_t time = glug_battery_time();

    CU_ASSERT_EQUAL(time / 60 / 60, mock_hours());
    CU_ASSERT_EQUAL(time / 60 % 60, mock_minutes());
    CU_ASSERT_EQUAL(time % 60, mock_seconds());
}

int main(void)
{
    int failures = 0;
    CU_pSuite suite = create_suite("battery stats", before_each, NULL);
    if (!suite) return CU_get_error();

    CU_add_test(suite, "no batteries", test_no_batteries);
    CU_add_test(suite, "no ac && no batteries == unknown", test_unknown_battery_state);
    CU_add_test(suite, "charged batteries", test_batteries_charged);
    CU_add_test(suite, "charging batteries w/ AC", test_batteries_charging);
    CU_add_test(suite, "discharging batteries", test_batteries_discharging);
    CU_add_test(suite, "mixed battery states w/o AC", test_batteries_mixed_disc);
    CU_add_test(suite, "mixed battery states w/ AC", test_batteries_mixed_charging);
    CU_add_test(suite, "battery % of charged", test_batteries_pct_charged);
    CU_add_test(suite, "battery time left", test_batteries_time);

    failures = run_tests(CU_BRM_VERBOSE);
    CU_cleanup_registry();

    return failures;
}
