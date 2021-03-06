cmake_minimum_required(VERSION 3.7)

project(example)

find_package(glug_power REQUIRED)
set(GLUG_TARGET_NAME example-glug_power)
set(GLUG_TARGET_NAME++ example-glug_power_cpp)

# create simple example with simple dependencies
function (add_example)
    set(OPTIONS)
    set(SINGLE_VALS TARGET_NAME)
    set(MULTI_VALS SRC LINK_LIBS)
    cmake_parse_arguments(EXAMPLE "${OPTIONS}" "${SINGLE_VALS}" "${MULTI_VALS}" ${ARGN})

    add_executable(${EXAMPLE_TARGET_NAME} ${EXAMPLE_SRC})
    target_link_libraries(${EXAMPLE_TARGET_NAME} ${EXAMPLE_LINK_LIBS})

    set_target_properties(
        ${EXAMPLE_TARGET_NAME}
        PROPERTIES
            INSTALL_RPATH "$ORIGIN;@loader_path"
            BUILD_WITH_INSTALL_RPATH TRUE
    )
endfunction()

add_example(
    TARGET_NAME
        ${GLUG_TARGET_NAME}
    SRC
        c/main.c
    LINK_LIBS
        glug::power
)

add_example(
    TARGET_NAME
        ${GLUG_TARGET_NAME++}
    SRC
        c++/main.cpp
    LINK_LIBS
        glug::power
)

target_compile_features(
    ${GLUG_TARGET_NAME++}
    PUBLIC
        cxx_std_11
)
set_target_properties(
    ${GLUG_TARGET_NAME++}
    PROPERTIES
        CXX_EXTENSIONS OFF
)
