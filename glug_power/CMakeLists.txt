cmake_minimum_required(VERSION 3.7)

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

detect_os(IS_WIN IS_OSX IS_LIN IS_BSD)

# configure files
set(CONFIGURED_OUT_ROOT ${CMAKE_CURRENT_BINARY_DIR}/configured)
configure_file(include/glug/power/version.h.in ${CONFIGURED_OUT_ROOT}/include/glug/power/version.h)

include(common_src.cmake)

include(windows.cmake)
include(osx.cmake)
include(linux.cmake)
include(bsd.cmake)

set_compilation_props("${WIN_SOURCE}"    FALSE)
set_compilation_props("${OSX_SOURCE}"    FALSE)
set_compilation_props("${LIN_SOURCE}"    FALSE)
set_compilation_props("${BSD_SOURCE}"    FALSE)
set_compilation_props("${BINDINGS}"      FALSE)

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
    ${BINDINGS}
)

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

# install the library
install(
    TARGETS
        glug_power
    EXPORT
        Find-glug_power
    DESTINATION
        lib
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

# export the package to be included in other projects
export(PACKAGE glug_power)
export(
    TARGETS
        glug_power
    FILE
        glug_power-config.cmake
)

# install export file
install(
    EXPORT
        Find-glug_power
    DESTINATION
        cmake
)
