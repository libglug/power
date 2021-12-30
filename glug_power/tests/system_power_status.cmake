set(TEST_TARGET "system_power_status")

list(
    APPEND
    TEST_SOURCE
    suites/system_power_status/system_power_status.c
    mocks/Windows.h
    mocks/Windows.c
)

list(
    APPEND
    TEST_LIB_SOURCE
    system_power_status/system_power_status.h
    system_power_status/system_power_status.c
)

list(
    APPEND
    TEST_MOCKS
    GetSystemPowerStatus
)
