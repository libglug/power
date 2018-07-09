set(CMAKE_ROOT ${PROJECT_SOURCE_DIR}/cmake)
include(${CMAKE_ROOT}/compile.cmake)
include(${CMAKE_ROOT}/export.cmake)
include(${CMAKE_ROOT}/os.cmake)

set(POW_SRC_ROOT ${GLUG_POW_ROOT}/src)
set(POW_INC_ROOT ${POW_INCLUDE_ROOT}/glug)

set(POW_HEADERS
    ${POW_INC_ROOT}/power.h
    ${POW_INC_ROOT}/power/power.h
    ${POW_INC_ROOT}/power/battery_status.h
    ${POW_INC_ROOT}/power/power_supply.h
)

set(POW_SOURCES
)

# set platform sources
set(WIN32_POW_ROOT ${POW_SRC_ROOT}/win32)
set(WIN32_SOURCES
    ${WIN32_POW_ROOT}/power.cpp
)

set(MACOS_POW_ROOT ${POW_SRC_ROOT}/macos)
set(MACOS_SOURCES

)

set(LINUX_POW_ROOT ${POW_SRC_ROOT}/linux)
set(LINUX_SOURCES
    ${LINUX_POW_ROOT}/power.cpp
)

# change compilation rules based on target os
set_compilation_props("${WIN32_SOURCES}" GLUG_OS_WIN32)
set_compilation_props("${MACOS_SOURCES}" GLUG_OS_MACOS)
set_compilation_props("${LINUX_SOURCES}" GLUG_OS_LINUX)

if(${GLUG_OS_WIN32})

    add_win32_exports()

elseif(${GLUG_OS_MACOS})

    add_linux_exports()

elseif(${GLUG_OS_LINUX})

    add_linux_exports()

endif()

add_library(
    ${CMAKE_PROJECT_NAME}
    SHARED
    ${POW_HEADERS}
    ${POW_SOURCES}
    ${WIN32_SOURCES}
    ${MACOS_SOURCES}
    ${LINUX_SOURCES}
)

if (DEFINED EXT_LIBS)

    target_link_libraries(${CMAKE_PROJECT_NAME} ${EXT_LIBS})

endif()

install(
    TARGETS ${CMAKE_PROJECT_NAME}
    DESTINATION ${GLUG_DIST_DIR}/lib
)

install(
    DIRECTORY ${POW_INC_ROOT}
    DESTINATION ${GLUG_DIST_DIR}/include
)

install(
    DIRECTORY ${PROJECT_SOURCE_DIR}/common_headers/include
    DESTINATION ${GLUG_DIST_DIR}
)
