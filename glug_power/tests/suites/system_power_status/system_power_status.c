#include <CUnit/Basic.h>
#include <CUnit/Assert.h>

#include <suites/create_suite.h>
#include <mocks/Windows.h>

#include <src/system_power_status/system_power_status.h>

static void before_each(void)
{
    set_ac_status(AC_LINE_ONLINE);
    set_battery_flag(BATTERY_FLAG_NO_BATTERY);
    set_battery_life(-1);
    set_battery_time(-1);
}

static void test_ac_connected(void)
{
    enum ac_line_state ac;

    set_ac_status(AC_LINE_ONLINE);
    ac = ac_line_status();
    CU_ASSERT_EQUAL(ac, ac_online);

    set_ac_status(AC_LINE_OFFLINE);
    ac = ac_line_status();
    CU_ASSERT_EQUAL(ac, ac_offline);

    set_ac_status(AC_LINE_UNKNOWN);
    ac = ac_line_status();
    CU_ASSERT_EQUAL(ac, ac_unknown);
}

static void test_battery_charge_state(void)
{
    enum battery_flag flags;
    set_ac_status(AC_LINE_OFFLINE);

    set_battery_flag(BATTERY_FLAG_NO_BATTERY);
    flags = battery_flag();
    CU_ASSERT_EQUAL(flags, bf_none);

    set_battery_flag(BATTERY_FLAG_UNKNOWN);
    flags = battery_flag();
    CU_ASSERT_EQUAL(flags, bf_unknown);

    // TODO ...
//    set_battery_flag(BATTERY_FLAG_HIGH);
//    state = battery_charge_state();
//    CU_ASSERT(state & bf_high);

//    set_battery_flag(BATTERY_FLAG_LOW);
//    state = battery_charge_state();
//    CU_ASSERT(state & bf_low);

//    set_battery_flag(BATTERY_FLAG_CRITICAL);
//    state = battery_charge_state();
//    CU_ASSERT(state & bf_critical);

    set_ac_status(AC_LINE_ONLINE);
    set_battery_flag(BATTERY_FLAG_LOW | BATTERY_FLAG_CHARGING);
    flags = battery_flag();
    CU_ASSERT(flags & bf_charging);

    set_battery_flag(BATTERY_FLAG_HIGH);
    flags = battery_flag();
    CU_ASSERT(flags & bf_high);
}

static void test_battery_life_percent(void)
{
    int8_t life = 0, expected;

    expected = 17;
    set_battery_life(expected);
    life = battery_life_percent();
    CU_ASSERT_EQUAL(life, expected);

    expected = 100;
    set_battery_life(expected);
    life = battery_life_percent();
    CU_ASSERT_EQUAL(life, expected);

    expected = -1;
    set_battery_life(expected);
    life = battery_life_percent();
    CU_ASSERT_EQUAL(life, expected);
}

static void test_battery_life_time(void)
{
    int32_t time = 0, expected;

    expected = 1234;
    set_battery_time(expected);
    time = battery_life_time();
    CU_ASSERT_EQUAL(time, expected);

    expected = 555;
    set_battery_time(expected);
    time = battery_life_time();
    CU_ASSERT_EQUAL(time, expected);

    expected = -1;
    set_battery_time(expected);
    time = battery_life_time();
    CU_ASSERT_EQUAL(time, expected);
}

int main(void)
{
    CU_pSuite suite = create_suite("system_power_status", before_each, NULL);
    if (!suite) return CU_get_error();

    CU_add_test(suite, "A/C connected", test_ac_connected);
    CU_add_test(suite, "battery state", test_battery_charge_state);
    CU_add_test(suite, "battery life", test_battery_life_percent);
    CU_add_test(suite, "battery time", test_battery_life_time);

    return run_tests(CU_BRM_VERBOSE);
}
