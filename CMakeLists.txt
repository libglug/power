project(glug_power)
cmake_minimum_required(VERSION 2.8)

set(GLUG_POW_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_PROJECT_NAME})
set(POW_INCLUDE_ROOT ${GLUG_POW_ROOT}/include)
include_directories(${POW_INCLUDE_ROOT})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/common_headers/include)

set(GLUG_DIST_DIR ${CMAKE_BINARY_DIR}/dist)

add_subdirectory(glug_power/src)
add_subdirectory(example)
