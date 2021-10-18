set(TEST_TARGET "bridge_bsd")

list(
    APPEND
    TEST_SOURCE
    suites/bridge/bsd.c
    mocks/sysctl/sysctl.h
    mocks/sysctl/sysctl.c
)

list(
    APPEND
    TEST_LIB_SOURCE
    power_bridge.h
    power_bridge_bsd.c
)
