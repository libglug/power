function(add_unit_test)
    set(SINGLE_VALS TARGET)
    set(MULTI_VALS SOURCES INCLUDE_DIRS LINK_LIBS)
    cmake_parse_arguments(UT "" "${SINGLE_VALS}" "${MULTI_VALS}" "${ARGN}")

    add_executable(
        ${UT_TARGET}
        create_suite.h
        create_suite.c
        ${UT_SOURCES}
    )

    set(TEST_TARGETS ${TEST_TARGETS} ${UT_TARGET} PARENT_SCOPE)

    target_compile_definitions(
        ${UT_TARGET}
        PRIVATE
            _CRT_SECURE_NO_WARNINGS # clear the secure warnings for things like strcat
            GLUG_LIB_LOCAL=
            GLUG_LIB_API=
    )

    target_include_directories(
        ${UT_TARGET}
        PRIVATE
            ${UT_INCLUDE_DIRS}
    )

    target_link_libraries(
        ${UT_TARGET}
        CUnit
    )

    add_test(${UT_TARGET} ${UT_TARGET})
endfunction()
