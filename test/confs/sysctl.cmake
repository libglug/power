set(TEST_TARGET "sysctl")

set(TEST_SOURCE suites/sysctl/sysctl.c)

list(
    APPEND
    TEST_LIB_SOURCE
    sysctl/sysctl.h
    sysctl/ac.c
    sysctl/battery.c
)

list(
    APPEND
    TEST_MOCK_SOURCE
    mocks/sys/sysctl.h
    mocks/sys/sysctl.c
)

list(
    APPEND
    TEST_MOCKS
    sysctlbyname
)
