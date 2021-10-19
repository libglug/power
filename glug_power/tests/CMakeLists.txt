add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/cunit/CUnit EXCLUDE_FROM_ALL)

find_package(glug_power REQUIRED)

set(LIB_ROOT ${CMAKE_CURRENT_LIST_DIR}/..)
set(LIB_SRC_ROOT ${LIB_ROOT}/src)
set(LIB_INC_ROOT ${LIB_ROOT}/include)

function(add_test_by_conf TEST_CONF)
    include(${TEST_CONF})
    set(TEST_TARGET "test-${TEST_TARGET}")

    list(
        TRANSFORM
            TEST_LIB_SOURCE
        PREPEND
            ${LIB_SRC_ROOT}/
    )

    add_executable(
        ${TEST_TARGET}
        EXCLUDE_FROM_ALL
        ${TEST_SOURCE}
        ${TEST_LIB_SOURCE}
        suites/create_suite.h
        suites/create_suite.c
        asserts/battery_state.h
        asserts/battery_state.c
    )

    target_include_directories(
        ${TEST_TARGET}
        PRIVATE
            ${LIB_ROOT}
            .
            mocks
            ${LIB_SRC_ROOT}
            ${LIB_INC_ROOT}
            ${TEST_INCLUDE_DIRS}
    )

    target_link_libraries(
        ${TEST_TARGET}
        CUnit
    )

    target_compile_definitions(
        ${TEST_TARGET}
        PRIVATE
            GLUG_LIB_LOCAL=
            GLUG_LIB_API=
    )

    foreach(DEF IN LISTS TEST_DEFS)
        target_compile_definitions(
            ${TEST_TARGET}
            PRIVATE
                ${DEF}
        )
    endforeach()

    foreach(MOCK IN LISTS TEST_MOCKS)
        target_compile_definitions(
            ${TEST_TARGET}
            PRIVATE
                ${MOCK}=${MOCK}_mocked
        )
    endforeach()

    list(
        APPEND
        TEST_TARGETS
        ${TEST_TARGET}
    )

    add_test(${TEST_TARGET} ${TEST_TARGET})
    set(TEST_TARGETS ${TEST_TARGETS} PARENT_SCOPE)
endfunction()

# unit tests
list(
    APPEND
    TEST_TARGETS
)

add_test_by_conf(system_power_status.cmake)
add_test_by_conf(sysctl.cmake)
add_test_by_conf(bridge-win.cmake)
add_test_by_conf(bridge-bsd.cmake)
add_test_by_conf(power.cmake)

foreach(TEST_TARGET IN LISTS TEST_TARGETS)
    add_custom_command(
        TARGET
            ${TEST_TARGET} POST_BUILD
        # copy the CUnit library to the same directory as the test binaries
        COMMAND
            ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:CUnit> $<TARGET_FILE_DIR:${TEST_TARGET}>
    )
endforeach()

# add the "check" target to build all tests
add_custom_target(
    check
    DEPENDS
        ${TEST_TARGETS}
)
