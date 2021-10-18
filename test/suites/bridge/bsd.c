#include <CUnit/Basic.h>
#include <CUnit/Assert.h>

#include <suites/create_suite.h>
#include <asserts/battery_state.h>

#include <../src/battery_state_t.h>
#include <../src/power_bridge.h>
#include <mocks/sysctl/sysctl.h>

void before_each(void)
{
    set_ac_connected(glug_true);
    set_battery_connected(glug_false);
    set_battery_life(-1);
    set_battery_time(-1);
}

void test_has_ac(void)
{
    glug_bool_t ac = glug_false;

    // connected
    set_ac_connected(glug_true);
    ac = has_ac();
    CU_ASSERT(ac);

    // disconnected
    set_ac_connected(glug_false);
    ac = has_ac();
    CU_ASSERT(!ac);
}

void test_battery_count()
{
    size_t count = 0;

    // has batteries
    set_battery_connected(glug_true);
    battery_count(&count);
    CU_ASSERT_EQUAL(count, 1);

    // no batteries
    set_battery_connected(glug_false);
    battery_count(&count);
    CU_ASSERT_EQUAL(count, 0);
}

void test_battery_state(void)
{
    struct battery_state state;

    // no batteries
    set_charge_state(cs_none);
    battery_state(&state);
    assert_battery_state_equal(&state, &(struct battery_state){ 0, 0, 0 });

    // unknown batteries
    set_charge_state(cs_unknown);
    battery_state(&state);
    assert_battery_state_equal(&state, &(struct battery_state){ 0, 0, 0 });

    // charged battery
    set_charge_state(cs_charged);
    battery_state(&state);
    assert_battery_state_equal(&state, &(struct battery_state){ 1, 0, 1 });

    // charging battery
    set_charge_state(cs_charging);
    battery_state(&state);
    assert_battery_state_equal(&state, &(struct battery_state){ 1, 1, 0 });

    // cdisharging battery
    set_charge_state(cs_discharging);
    battery_state(&state);
    assert_battery_state_equal(&state, &(struct battery_state){ 1, 0, 0 });
}

void test_battery_level(void)
{
    int8_t level, expected;

    expected = 99;
    set_battery_life(expected);
    level = battery_level();
    CU_ASSERT_EQUAL(level, expected);

    expected = -1;
    set_battery_life(expected);
    level = battery_level();
    CU_ASSERT_EQUAL(level, expected);
}

void test_battery_time(void)
{
    int32_t time, expected;

    expected = 12345;
    set_battery_time(expected);
    time = battery_time();
    CU_ASSERT_EQUAL(time, expected);

    expected = -1;
    set_battery_time(expected);
    time = battery_time();
    CU_ASSERT_EQUAL(time, expected);
}

int main(void)
{
    CU_pSuite suite = create_suite("bsd_bridge", before_each, NULL);
    if (!suite) return CU_get_error();

    CU_add_test(suite, "has A/C", test_has_ac);
    CU_add_test(suite, "has battery", test_battery_count);
    CU_add_test(suite, "battery state", test_battery_state);
    CU_add_test(suite, "battery level", test_battery_level);
    CU_add_test(suite, "battery time", test_battery_time);


    return run_tests(CU_BRM_VERBOSE);
}
