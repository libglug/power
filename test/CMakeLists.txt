add_subdirectory(CUnit/CUnit EXCLUDE_FROM_ALL)
include(CUnit/CUnit/cmake/add_unit_test.cmake)

set(SRC_ROOT ../glug_power)

function(create_unit_test)
    set(SINGLE_VALS TARGET)
    set(MULTI_VALS SOURCES INCLUDE_DIRS)
    cmake_parse_arguments(TEST "" "${SINGLE_VALS}" "${MULTI_VALS}" "${ARGN}")

    add_unit_test(
        TARGETNAME
            ${TEST_TARGET}
        SOURCES
            "${TEST_SOURCES}"
        INCLUDE_DIRS
            "${INCLUDE_DIRS}"
        LINK_LIBS
            CUnit
        DEFINES
            GLUG_LIB_LOCAL=
            GLUG_LIB_API=
    )
endfunction()

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
create_unit_test(
    TARGET
        unit-powerstats
    SOURCES
        unit/power_stats.c
        ${SRC_ROOT}/src/power.c
        create_suite.h
        ${MOCKS}
    INCLUDE_DIRS
        ${INCLUDE_DIRS}
)

create_unit_test(
    TARGET
        win32-power
    SOURCES
        unit/win32_power.c
        unit/mocks/windows.mock.h
        ${SRC_ROOT}/src/battery_list.h
        ${SRC_ROOT}/src/battery_platform.h
        ${SRC_ROOT}/src/win32/power.c
        ${SRC_ROOT}/src/power_platform.h
        create_suite.h
    INCLUDE_DIRS
        ${INCLUDE_DIRS}
)

# create a custom target which builds tests and their dependencies
# (bug in CMake? (https://gitlab.kitware.com/cmake/cmake/issues/8774))
add_custom_target(
    check
    ALL
    DEPENDS
        # add other tests executables here
        CUnit unit-powerstats win32-power
)

# copy the CUnit library to the same directory
add_custom_command(
    TARGET
        check POST_BUILD
    COMMAND
        ${CMAKE_COMMAND} -E copy
            $<TARGET_FILE:CUnit> ${CMAKE_CURRENT_BINARY_DIR}
)
