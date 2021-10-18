cmake_minimum_required(VERSION 3.7)
include(CMakePackageConfigHelpers)

include(cmake/version.cmake)

include(cmake/detect_os.cmake)
include(cmake/set_compilation_props.cmake)
include(cmake/link_libs.cmake)
include(cmake/set_export_defs.cmake)

parse_git_tag_version(VER_MAJOR VER_MINOR VER_PATCH VER_META VER_REV VER_HASH VER_FULL)
set(FULL_VERSION ${VER_MAJOR}.${VER_MINOR}.${VER_PATCH}-${VER_META})

project(
    glug_power
    LANGUAGES
        C
    VERSION
        ${VER_MAJOR}.${VER_MINOR}.${VER_PATCH}
)

option(BUILD_STATIC "Build as a static library instead of shared?" OFF)

detect_os(IS_WIN IS_OSX IS_LIN IS_BSD IS_HAIKU)

# configure files
set(CONFIGURED_OUT_ROOT ${CMAKE_CURRENT_BINARY_DIR}/configured)
configure_file(include/glug/power/version.h.in ${CONFIGURED_OUT_ROOT}/include/glug/power/version.h)

include(common_src.cmake)

include(windows.cmake)
include(osx.cmake)
include(linux.cmake)
include(bsd.cmake)
include(haiku.cmake)

set(NULL_SOURCE power_bridge_null.c)

set_compilation_props("${BINDINGS}"     FALSE)
set_compilation_props("${WIN_SOURCE}"   FALSE)
set_compilation_props("${OSX_SOURCE}"   FALSE)
set_compilation_props("${LIN_SOURCE}"   FALSE)
set_compilation_props("${BSD_SOURCE}"   FALSE)
set_compilation_props("${HAIKU_SOURCE}" FALSE)
set_compilation_props("${NULL_SOURCE}"  FALSE)

if (${IS_WIN})
    set(PLATFORM_SRC  "${WIN_SOURCE}")
    set(PLATFORM_LIBS "${WIN_LIBS}")
elseif (${IS_OSX})
    set(PLATFORM_SRC  "${OSX_SOURCE}")
    set(PLATFORM_LIBS "${OSX_LIBS}")
elseif (${IS_LIN})

    set(PLATFORM_SRC  "${LIN_SOURCE}")
    set(PLATFORM_LIBS "${LIN_LIBS}")
elseif (${IS_BSD})
    set(PLATFORM_SRC  "${BSD_SOURCE}")
    set(PLATFORM_LIBS "${BSD_LIBS}")
elseif (${IS_HAIKU})
    set(PLATFORM_SRC  "${HAIKU_SOURCE}")
    set(PLATFORM_LIBS "${HAIKU_LIBS}")
else ()
    set(PLATFORM_SRC  "${NULL_SOURCE}")
    set(PLATFORM_LIBS "${NULL_LIBS}")
endif()

set_compilation_props("${PLATFORM_SRC}" TRUE)

# set the library type
set(LIB_TYPE SHARED)
if (BUILD_STATIC)
    set(LIB_TYPE STATIC)
endif()

add_library(
    glug_power
    ${LIB_TYPE}
    ${COMMON_SOURCE}
    ${WIN_SOURCE}
    ${OSX_SOURCE}
    ${LIN_SOURCE}
    ${BSD_SOURCE}
    ${HAIKU_SOURCE}
    ${BINDINGS}
)

add_library(glug::power ALIAS glug_power)

link_libs(glug_power "${PLATFORM_LIBS}")
set_export_defs(glug_power ${BUILD_STATIC} ${IS_WIN})

target_include_directories(
    glug_power
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CONFIGURED_OUT_ROOT}/include> # because "version.h" is a configured file
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/common_headers/include>
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    INTERFACE
        $<INSTALL_INTERFACE:include>
)

set(PROJECT_CONFIG_FILE glug_power-config.cmake)
configure_package_config_file(
    cmake/config.cmake.in
    ${PROJECT_CONFIG_FILE}
    INSTALL_DESTINATION
        cmake
)

# install the lib's headers
install(
    DIRECTORY
        include/
    DESTINATION
        include
    FILES_MATCHING
        PATTERN "*"
        PATTERN "*.in" EXCLUDE
)

# install the lib's configured version file
install(
    FILES
        ${CONFIGURED_OUT_ROOT}/include/glug/power/version.h
    DESTINATION
        include/glug/power
)

# install the common_headers
install(
    DIRECTORY
        common_headers/include/
    DESTINATION
        include
    FILES_MATCHING
        PATTERN "*"
        PATTERN "*.in$" EXCLUDE
)

# install the library and its exports
install(
    TARGETS
        glug_power
    EXPORT
        glug_power-targets
    RUNTIME DESTINATION
        lib
    LIBRARY DESTINATION
        lib
    ARCHIVE DESTINATION
        lib
)

# export the package to be included in other projects
install(
    EXPORT
        glug_power-targets
    FILE
        glug_power-targets.cmake
    NAMESPACE
        glug::
    DESTINATION
        cmake
)
export(
    EXPORT
        glug_power-targets
    FILE
        glug_power-config.cmake
    NAMESPACE
        glug::
)

export(PACKAGE glug_power)

enable_testing()
add_subdirectory(tests)
