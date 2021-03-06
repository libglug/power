cmake_minimum_required(VERSION 3.7)

project(glug_power_suite)

# disable find_package in any subproject when trying to find the main project library
macro(find_package)
    if (NOT "${ARGV0}" STREQUAL glug_power)
        _find_package(${ARGV})
    endif()
endmacro()

# add the library subproject
add_subdirectory(glug_power)

# add the "examples" target to build all examples
add_subdirectory(example EXCLUDE_FROM_ALL)

get_property(
    EXAMPLE_TARGETS
    DIRECTORY
        example
    PROPERTY
        BUILDSYSTEM_TARGETS
)

add_custom_target(
    examples
    DEPENDS
        ${EXAMPLE_TARGETS}
)

# copy the library to the example build directory
add_custom_command(
    TARGET
        examples POST_BUILD
    COMMAND
        ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:glug_power> example
)

# create a custom "install-examples" target to install the examples without being part of ALL
add_custom_target(
    install-examples
    DEPENDS
        ${EXAMPLE_TARGETS}
)

foreach(EXAMPLE_TARGET IN LISTS EXAMPLE_TARGETS)
    add_custom_command(
        TARGET
            install-examples
        COMMAND
            ${CMAKE_COMMAND} -E copy
                $<TARGET_FILE:${EXAMPLE_TARGET}>
                ${CMAKE_INSTALL_PREFIX}/examples/$<TARGET_FILE_NAME:${EXAMPLE_TARGET}>
    )
endforeach()

enable_testing()
include(test/tests.cmake)
