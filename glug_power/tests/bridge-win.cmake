set(TEST_TARGET "bridge_windows")

list(
    APPEND
    TEST_SOURCE
    suites/bridge/win.c
    mocks/system_power_status/system_power_status.h
    mocks/system_power_status/system_power_status.c

)

list(
    APPEND
    TEST_LIB_SOURCE
    power_bridge.h
    power_bridge_win.c
)
