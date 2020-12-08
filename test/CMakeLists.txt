add_subdirectory(CUnit/CUnit EXCLUDE_FROM_ALL)
include(add_unit_test.cmake)

set(TESTED_LIB glug_power)

set(LIB_SRC ../${TESTED_LIB}/src)
list(
    APPEND
    UNIT_INCLUDE_DIRS
    .
    ../${TESTED_LIB}/src
    ../${TESTED_LIB}/include
    ../${TESTED_LIB}/common_headers/include
)

# unit tests
list(
    APPEND
    TEST_TARGETS
)

add_unit_test(
    TARGET
        unit-powerstats
    SOURCES
        unit/power_stats.c
        ${LIB_SRC}/power.c
    INCLUDE_DIRS
        ${UNIT_INCLUDE_DIRS}
)

# copy the executable to this build directory (MSVC likes to hide it in Debug/Release folders)
add_custom_target(
    check
    ALL
    DEPENDS
        CUnit ${TEST_TARGETS} ${TESTED_LIB}
)

add_custom_command(
    TARGET
        check POST_BUILD
    # copy the CUnit library to the same directory as the test binaries
    COMMAND
        ${CMAKE_COMMAND} -E copy
            $<TARGET_FILE:CUnit> ${CMAKE_CURRENT_BINARY_DIR}
#    TODO: for integration or e2e test
#    # copy the library to the same directory as the test binaries
#    COMMAND
#        ${CMAKE_COMMAND} -E copy
#            $<TARGET_FILE:${TESTED_LIB}> ${CMAKE_CURRENT_BINARY_DIR}
)
