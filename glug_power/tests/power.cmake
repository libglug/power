set(TEST_TARGET "power")

list(
    APPEND
    TEST_SOURCE
    suites/power/power.c
    mocks/power_bridge.h
    mocks/power_bridge.c
)

list(
    APPEND
    TEST_LIB_SOURCE
    power.c
)

list(
    APPEND
    TEST_DEFS
    GLUG_EXTERN_START=
    GLUG_EXTERN_END=
)
