cmake_minimum_required(VERSION 3.7)

project(glug_power_suite)

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
add_custom_target(
    copy_lib_to_examples
)
add_custom_command(
    TARGET
        copy_lib_to_examples POST_BUILD
    COMMAND
        ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:glug::power> example
)
add_dependencies(examples copy_lib_to_examples)
foreach(EXAMPLE_TARGET IN LISTS EXAMPLE_TARGETS)
    add_dependencies(${EXAMPLE_TARGET} copy_lib_to_examples)
endforeach()

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
add_custom_command(
    TARGET
        install-examples
    COMMAND
        ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:glug::power> ${CMAKE_INSTALL_PREFIX}/examples
)

enable_testing()
include(test/tests.cmake)
