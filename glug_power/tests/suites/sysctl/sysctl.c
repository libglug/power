#include <CUnit/Basic.h>
#include <CUnit/Assert.h>

#include <suites/create_suite.h>
#include <mocks/sys/sysctl.h>

#include <src/sysctl/sysctl.h>

void before_each(void)
{
    clear_sysctl();
}

void test_has_ac(void)
{
    glug_bool_t ac = glug_false;

    // available and online
    set_acline(1, 1);
    ac = ac_connected();
    CU_ASSERT(ac);

    // available and offline
    set_acline(1, 0);
    ac = ac_connected();
    CU_ASSERT(!ac);

    // not available
    set_acline(0, 1);
    ac = ac_connected();
    CU_ASSERT(!ac);
}

void test_battery_count(void)
{
    glug_bool_t has_batts = glug_false;

    // available and 2 batteries
    set_battery_units(1, 2);
    has_batts = battery_connected();
    CU_ASSERT(has_batts);

    // available and 1 battery
    set_battery_units(1, 1);
    has_batts = battery_connected();
    CU_ASSERT(has_batts);

    // available and no batteries
    set_battery_units(1, 0);
    has_batts = battery_connected();
    CU_ASSERT(has_batts);

    // not available
    set_battery_units(0, 2);
    has_batts = battery_connected();
    CU_ASSERT(!has_batts);
}

void test_battery_state(void)
{
    enum charge_state state, expected;
    set_battery_units(1, 1);

    // available and charging
    expected = cs_charging;
    set_battery_state(1, 2);
    state = battery_charge_state();
    CU_ASSERT_EQUAL(state, expected);

    // available and charged
    expected = cs_charged;
    set_battery_state(1, 0);
    state = battery_charge_state();
    CU_ASSERT_EQUAL(state, expected);

    // available and discharging
    expected = cs_discharging;
    set_battery_state(1, 1);
    state = battery_charge_state();
    CU_ASSERT_EQUAL(state, expected);

    // available and an unknown status
    expected = cs_unknown;
    set_battery_state(1, -1);
    state = battery_charge_state();
    CU_ASSERT_EQUAL(state, expected);

    // not available (unavailable state)
    expected = cs_unknown;
    set_battery_state(0, 2);
    state = battery_charge_state();
    CU_ASSERT_EQUAL(state, expected);

    // not available (unavailable battery.units)
    expected = cs_unknown;
    set_battery_units(0, 1);
    set_battery_state(1, 1);
    state = battery_charge_state();
    CU_ASSERT_EQUAL(state, expected);
}

void test_battery_level(void)
{
    int32_t life, expected;

    // available and valid time
    expected = 99;
    set_battery_time(1, expected);
    life = battery_life_time();
    CU_ASSERT_EQUAL(life, expected * 60);

    // available and unknown time
    expected = -1;
    set_battery_time(1, expected);
    life = battery_life_time();
    CU_ASSERT_EQUAL(life, expected);

    // not available
    set_battery_time(0, 15);
    life = battery_life_time();
    CU_ASSERT_EQUAL(life, -1);
}

void test_battery_time(void)
{
    int32_t time, expected;

    // available and valid time
    expected = 120;
    set_battery_time(1, expected);
    time = battery_life_time();
    CU_ASSERT_EQUAL(time, expected * 60);

    // available and unknown time
    expected = -1;
    set_battery_time(1, expected);
    time = battery_life_time();
    CU_ASSERT_EQUAL(time, expected);

    // not available
    set_battery_time(0, 1234);
    time = battery_life_time();
    CU_ASSERT_EQUAL(time, -1);
}

int main(void)
{
    CU_pSuite suite = create_suite("sysctl", before_each, NULL);
    if (!suite) return CU_get_error();

    CU_add_test(suite, "A/C connected", test_has_ac);
    CU_add_test(suite, "battery connected", test_battery_count);
    CU_add_test(suite, "battery state", test_battery_state);
    CU_add_test(suite, "battery life", test_battery_level);
    CU_add_test(suite, "battery time", test_battery_time);

    return run_tests(CU_BRM_VERBOSE);
}
