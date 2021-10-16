set(TEST_TARGET "bridge-bsd")

set(TEST_SOURCE suites/bridge/bsd.c)

list(
    APPEND
    TEST_LIB_SOURCE
    power_bridge.h
    power_bridge_bsd.c
)

list(
    APPEND
    TEST_MOCK_SOURCE
    mocks/sysctl/sysctl.h
    mocks/sysctl/sysctl.c
)
