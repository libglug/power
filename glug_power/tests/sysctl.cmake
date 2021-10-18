set(TEST_TARGET "sysctl")

list(
    APPEND
    TEST_SOURCE
    suites/sysctl/sysctl.c
    mocks/sys/sysctl.h
    mocks/sys/sysctl.c
)

list(
    APPEND
    TEST_LIB_SOURCE
    sysctl/sysctl.h
    sysctl/ac.c
    sysctl/battery.c
)

list(
    APPEND
    TEST_MOCKS
    sysctlbyname
)
