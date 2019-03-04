add_subdirectory(CUnit/CUnit EXCLUDE_FROM_ALL)
include(CUnit/CUnit/cmake/add_unit_test.cmake)

set(SRC_ROOT ../glug_power)

# unit tests
list(
    APPEND
    INCLUDE_DIRS
    CUnit/CUnit/include
    ${SRC_ROOT}/common_headers/include
    ${SRC_ROOT}/include
    ${SRC_ROOT}/src
)
set(MOCK_DIR unit/mocks)
list(
    APPEND
    MOCKS
    ${MOCK_DIR}/ac.mock.h
    ${MOCK_DIR}/ac.mock.c
    ${MOCK_DIR}/battery_list.mock.h
    ${MOCK_DIR}/battery_list.mock.c
)
add_unit_test(
    TARGETNAME
        unit-powerstats
    SOURCES
        unit/power_stats.c
        ${SRC_ROOT}/src/power.c
        create_suite.h
        ${MOCKS}
    INCLUDE_DIRS
        ${INCLUDE_DIRS}
    LINK_LIBS
        CUnit
)

# create a custom target which builds tests and their dependencies
# (bug in CMake? (https://gitlab.kitware.com/cmake/cmake/issues/8774))
add_custom_target(
    check
    ALL
    DEPENDS
        # add other tests executables here
        CUnit unit-powerstats
)

# copy the CUnit library to the same directory
add_custom_command(
    TARGET
        check POST_BUILD
    COMMAND
        ${CMAKE_COMMAND} -E copy
            $<TARGET_FILE:CUnit> ${CMAKE_CURRENT_BINARY_DIR}
)
