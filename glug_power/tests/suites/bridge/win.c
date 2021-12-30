#include <CUnit/Basic.h>
#include <CUnit/Assert.h>

#include <suites/create_suite.h>
#include <asserts/battery_state.h>
#include <mocks/system_power_status/system_power_status.h>

#include <src/battery_state_t.h>
#include <src/power_bridge.h>

#include <glug/bool_t.h>

static void before_each(void)
{
    set_ac_line_status(ac_online);
    set_battery_flag(bf_none);
    set_battery_percent(-1);
    set_battery_time(-1);
}

static void test_has_ac(void)
{
    glug_bool_t ac = glug_false;

    // connected
    set_ac_line_status(ac_online);
    ac = has_ac();
    CU_ASSERT(ac);

    // disconnected
    set_ac_line_status(ac_offline);
    ac = has_ac();
    CU_ASSERT(!ac);
}

static void test_battery_count(void)
{
    size_t count = 0;

    // has batteries
    set_battery_flag(bf_high);
    battery_count(&count);
    CU_ASSERT_EQUAL(count, 1);

    // no batteries
    set_battery_flag(bf_none);
    battery_count(&count);
    CU_ASSERT_EQUAL(count, 0);
}

static void test_battery_state(void)
{
    struct battery_state state;

    // no batteries
    set_battery_flag(bf_none);
    battery_state(&state);
    assert_battery_state_equal(&state, &(struct battery_state){ 0, 0, 0 });

    // unknown batteries
    set_battery_flag(bf_unknown);
    battery_state(&state);
    assert_battery_state_equal(&state, &(struct battery_state){ 0, 0, 0 });

    // charged battery
    set_battery_flag(1);
    battery_state(&state);
    assert_battery_state_equal(&state, &(struct battery_state){ 1, 0, 1 });

    // charging battery
    set_battery_flag(bf_charging);
    battery_state(&state);
    assert_battery_state_equal(&state, &(struct battery_state){ 1, 1, 0 });

    // disharging battery
    set_ac_line_status(ac_offline);
    set_battery_flag(bf_high);
    battery_state(&state);
    assert_battery_state_equal(&state, &(struct battery_state){ 1, 0, 0 });
}

static void test_battery_level(void)
{
    int8_t level, expected;

    expected = 99;
    set_battery_percent(expected);
    level = battery_level();
    CU_ASSERT_EQUAL(level, expected);

    expected = -1;
    set_battery_percent(expected);
    level = battery_level();
    CU_ASSERT_EQUAL(level, expected);
}

static void test_battery_time(void)
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
    CU_pSuite suite = create_suite("windows bridge", before_each, NULL);
    if (!suite) return CU_get_error();

    CU_add_test(suite, "has A/C", test_has_ac);
    CU_add_test(suite, "has battery", test_battery_count);
    CU_add_test(suite, "battery state", test_battery_state);
    CU_add_test(suite, "battery level", test_battery_level);
    CU_add_test(suite, "battery time", test_battery_time);


    return run_tests(CU_BRM_VERBOSE);
}
