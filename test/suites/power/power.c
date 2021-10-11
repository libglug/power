#include <CUnit/Basic.h>
#include <CUnit/Assert.h>

#include <suites/create_suite.h>

#include <glug/power/power.h>
#include <mocks/power_bridge.h>

void before_each(void)
{
    set_ac(glug_true);
    set_batteries(0);
    set_charged_batteries(0);
    set_charging_batteries(0);
    set_battery_level(100);
    set_battery_time(4 * 60 * 60);
}

void after_each(void)
{

}

void test_power_supply(void)
{
    enum glug_power_supply supply;

    set_ac(glug_true);
    supply = glug_power_active_supply();
    CU_ASSERT_EQUAL(supply, glug_power_ac);

    set_ac(glug_false);
    supply = glug_power_active_supply();
    CU_ASSERT_EQUAL(supply, glug_power_unknown);

    // add case here for all dead batteries
}

void test_battery_status(void)
{
    enum glug_battery_status status;

    // no A/C and no batteries => unkonwn
    set_ac(glug_false);
    status = glug_power_battery_state();
    CU_ASSERT_EQUAL(status, glug_battery_unknown);

    // has A/C but no batteries => none
    set_ac(glug_true);
    status = glug_power_battery_state();
    CU_ASSERT_EQUAL(status, glug_battery_none);

    // no A/C and batteries (charged or charging) => discharging
    set_ac(glug_false);
    set_batteries(2);
    set_charged_batteries(1);
    set_charging_batteries(1);
    status = glug_power_battery_state();
    CU_ASSERT_EQUAL(status, glug_battery_discharging);

    // has A/C and charging batteries => charging
    set_ac(glug_true);
    set_batteries(4);
    set_charged_batteries(3);
    set_charging_batteries(1);
    status = glug_power_battery_state();
    CU_ASSERT_EQUAL(status, glug_battery_charging);

    // has A/C and all batteries charged => charged
    set_ac(glug_true);
    set_batteries(3);
    set_charged_batteries(3);
    set_charging_batteries(0);
    status = glug_power_battery_state();
    CU_ASSERT_EQUAL(status, glug_battery_charged);
}

void test_battery_level(void)
{
    int8_t level, expected;

    expected = 100;
    set_battery_level(expected);
    level = glug_power_battery_level();
    CU_ASSERT_EQUAL(level, expected);

    expected = 12;
    set_battery_level(expected);
    level = glug_power_battery_level();
    CU_ASSERT_EQUAL(level, expected);

    expected = -1;
    set_battery_level(expected);
    level = glug_power_battery_level();
    CU_ASSERT_EQUAL(level, expected);
}

void test_battery_time(void)
{
    int32_t time, expected;

    expected = 4 * 60 * 60 + 30;
    set_battery_time(expected);
    time = glug_power_battery_time();
    CU_ASSERT_EQUAL(time, expected);

    expected = (2 * 60 + 15) * 60 + 15;
    set_battery_time(expected);
    time = glug_power_battery_time();
    CU_ASSERT_EQUAL(time, expected);
}

int main(void)
{
    CU_pSuite suite = create_suite("power", before_each, after_each);
    if (!suite) return CU_get_error();

    CU_add_test(suite, "power supply", test_power_supply);
    CU_add_test(suite, "battery status", test_battery_status);
    CU_add_test(suite, "battery level", test_battery_level);
    CU_add_test(suite, "battery time", test_battery_time);

    return run_tests(CU_BRM_VERBOSE);
}
