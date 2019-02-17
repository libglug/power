cmake_minimum_required(VERSION 3.0)

set(VER_MAJOR 1)
set(VER_MINOR 0)
set(VER_PATCH 0)
project(glug_power VERSION ${VER_MAJOR}.${VER_MINOR}.${VER_PATCH})
include(cmake/add_gluglib.cmake)

option(BUILD_STATIC "Build as a static library instead of shared" "OFF")

set(SRC_ROOT src)
set(INC_ROOT include/glug)

list(
    APPEND
    COMMON_SOURCE
    ${INC_ROOT}/power.h
    ${INC_ROOT}/power/power.h
    ${INC_ROOT}/power/battery_status.h
    ${INC_ROOT}/power/power_supply.h
    ${SRC_ROOT}/power.c
    ${SRC_ROOT}/power_platform.h
    ${SRC_ROOT}/battery_platform.h
    ${SRC_ROOT}/battery_list.h
    ${SRC_ROOT}/battery_list.c
)

# Windows sources
set(WIN32_ROOT ${SRC_ROOT}/win32)
list(
    APPEND
    WIN32_SOURCE
    ${COMMON_SOURCE}
    ${WIN32_ROOT}/power.c
    ${WIN32_ROOT}/battery_node.c
)

# Mac OS sources
set(MACOS_ROOT ${SRC_ROOT}/macos)
list(
    APPEND
    MACOS_SOURCE
    ${COMMON_SOURCE}
    ${MACOS_ROOT}/power.c
    ${MACOS_ROOT}/battery_node.c)

# linux sources
set(LINUX_ROOT ${SRC_ROOT}/linux)
list(
    APPEND
    LINUX_SOURCE
    ${COMMON_SOURCE}
    ${LINUX_ROOT}/power.c
    ${LINUX_ROOT}/battery_node.c
)

add_gluglib(
    TARGET_NAME ${CMAKE_PROJECT_NAME}
    STATIC_BUILD ${BUILD_STATIC}
    WIN32_SOURCE ${WIN32_SOURCE}
    MACOS_SOURCE ${MACOS_SOURCE}
    LINUX_SOURCE ${LINUX_SOURCE}
    WIN32_LIBS
    MACOS_LIBS CoreFoundation IOKit
    LINUX_LIBS
)

target_include_directories(
    ${CMAKE_PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/common_headers/include>
    INTERFACE
        $<INSTALL_INTERFACE:include>
)

# install the library
install(
    TARGETS
        ${CMAKE_PROJECT_NAME}
    EXPORT
        Find${CMAKE_PROJECT_NAME}
    DESTINATION
        lib
)

#install the lib's headers
install(
    DIRECTORY
        include/
    DESTINATION
        include
)

# install the common_headers
install(
    DIRECTORY
        common_headers/include/
    DESTINATION
        include
    FILES_MATCHING PATTERN
        "*.h"
)

# export the package to be included in other projects
export(PACKAGE ${CMAKE_PROJECT_NAME})
export(
    TARGETS
        ${CMAKE_PROJECT_NAME}
    FILE
        ${CMAKE_PROJECT_NAME}-config.cmake
)

# install export file
install(
    EXPORT
        Find${CMAKE_PROJECT_NAME}
    DESTINATION
        cmake
)

