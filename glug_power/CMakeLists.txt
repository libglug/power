include(${PROJECT_SOURCE_DIR}/cmake/macros/add_gluglib.cmake)

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

set(WIN32_ROOT ${SRC_ROOT}/win32)
list(
    APPEND
    WIN32_SOURCE
    ${COMMON_SOURCE}
    ${WIN32_ROOT}/power.c
    ${WIN32_ROOT}/battery_node.c
)

set(MACOS_ROOT ${SRC_ROOT}/macos)
list(
    APPEND
    MACOS_SOURCE
    ${COMMON_SOURCE}
    ${MACOS_ROOT}/power.c
    ${MACOS_ROOT}/battery_node.c
)

set(LINUX_ROOT ${SRC_ROOT}/linux)
list(
    APPEND
    LINUX_SOURCE
    ${COMMON_SOURCE}
    ${LINUX_ROOT}/power.c
    ${LINUX_ROOT}/battery_node.c
)

if(${GLUG_OS_MACOS})
    find_library(APPLE_CF CoreFoundation)
    find_library(APPLE_IOKIT IOKit)
    set(EXT_LIBS ${APPLE_CF} ${APPLE_IOKIT})
endif()

set(GLUG_TARGET_NAME ${CMAKE_PROJECT_NAME})

add_gluglib(
    TARGET_NAME  ${GLUG_TARGET_NAME}
    WIN32_SOURCE ${WIN32_SOURCE}
    MACOS_SOURCE ${MACOS_SOURCE}
    LINUX_SOURCE ${LINUX_SOURCE}
    EXT_LIBS     ${EXT_LIBS}
)

# install the library
install(
    TARGETS ${GLUG_TARGET_NAME}
    DESTINATION ${GLUG_DIST_LIBR_DIR}
)

install(
    TARGETS ${GLUG_TARGET_NAME}
    DESTINATION ${GLUG_DIST_XMPL_DIR}
)
