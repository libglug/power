set(TEST_TARGET "power")

set(TEST_SOURCE suites/power/power.c)

list(
    APPEND
    TEST_LIB_SOURCE
    power.c
)

list(
    APPEND
    TEST_MOCK_SOURCE
    mocks/power_bridge.h
    mocks/power_bridge.c
)

list(
    APPEND
    TEST_DEFS
    GLUG_EXTERN_START=
    GLUG_EXTERN_END=
)

set(TEST_INCLUDE_DIRS)
