function(add_gluglib)
    set(OPTIONS)
    set(SINGLE_VALS STATIC_BUILD TARGET_NAME)
    set(
        MULTI_VALS
            WIN32_SOURCE MACOS_SOURCE LINUX_SOURCE BSD_SOURCE
            WIN32_LIBS MACOS_LIBS LINUX_LIBS BSD_LIBS
    )
    cmake_parse_arguments(GLUG "${OPTIONS}" "${SINGLE_VALS}" "${MULTI_VALS}" ${ARGN})

    detect_os()

    # make a giant list of all source files added to the project
    list(
        APPEND
        ALL_SOURCE
        ${GLUG_WIN32_SOURCE}
        ${GLUG_MACOS_SOURCE}
        ${GLUG_LINUX_SOURCE}
        ${GLUG_BSD_SOURCE}
    )

    # create a list of this platform's sources
    if (DEFINED GLUG_OS_WIN32)
        list(APPEND PLAT_SOURCE ${GLUG_WIN32_SOURCE})
    elseif (DEFINED GLUG_OS_MACOS)
        list(APPEND PLAT_SOURCE ${GLUG_MACOS_SOURCE})
    elseif (DEFINED GLUG_OS_LINUX)
        list(APPEND PLAT_SOURCE ${GLUG_LINUX_SOURCE})
    elseif (DEFINED GLUG_OS_BSD)
        list(APPEND PLAT_SOURCE ${GLUG_BSD_SOURCE})
    endif()

    # remove the source files from the "all" list for the current platform
    list(REMOVE_ITEM ALL_SOURCE ${PLAT_SOURCE})

    # compile the sources for this platform only
    set_compilation_props("${ALL_SOURCE}" FALSE)
    set_compilation_props("${PLAT_SOURCE}" TRUE)

    # set the library type
    set(LIB_TYPE SHARED)
    if (GLUG_STATIC_BUILD)
        set(LIB_TYPE STATIC)
    endif()

    # create the library target
    add_library(${GLUG_TARGET_NAME} ${LIB_TYPE} ${ALL_SOURCE} ${PLAT_SOURCE})

    # set the defs for the target
    set(WINDEFS FALSE)
    if (DEFINED GLUG_OS_WIN32)
        set(WINDEFS TRUE)
    endif()
    set_export_defs(${GLUG_TARGET_NAME} ${GLUG_STATIC_BUILD} ${WINDEFS})

    # link to other libraries
    if (DEFINED GLUG_OS_WIN32)
        link_libs(${GLUG_TARGET_NAME} "${GLUG_WIN32_LIBS}")
    elseif (DEFINED GLUG_OS_MACOS)
        link_libs(${GLUG_TARGET_NAME} "${GLUG_MACOS_LIBS}")
    elseif (DEFINED GLUG_OS_LINUX)
        link_libs(${GLUG_TARGET_NAME} "${GLUG_LINUX_LIBS}")
    elseif (DEFINED GLUG_OS_BSD)
        link_libs(${GLUG_TARGET_NAME} "${GLUG_BSD_LIBS}")
    endif()

endfunction()

# toggle source compilation
function (set_compilation_props SOURCES_LIST SHOULD_COMPILE)
    if (${SHOULD_COMPILE})
        set(DONT_COMPILE FALSE)
    else()
        set(DONT_COMPILE TRUE)
    endif()

    foreach(FILE ${SOURCES_LIST})
        set_source_files_properties(${FILE} PROPERTIES HEADER_FILE_ONLY ${DONT_COMPILE})
    endforeach()

endfunction()

# find and link to each library for TARGET
function(link_libs TARGET LIBS)
    foreach(LIB ${LIBS})
        find_library(FOUND_LIB ${LIB})
        if (NOT FOUND_LIB)
            message(FATAL_ERROR "${LIB} not found")
        endif()
        list(
            APPEND
            FOUND_LIBS
            ${FOUND_LIB}
        )
        unset(FOUND_LIB CACHE)
    endforeach()
    target_link_librarIES(
        ${TARGET}
        ${FOUND_LIBS}
    )
endfunction()

# set symbol export defs
function (set_export_defs TARGET STATIC_BUILD WINDOWS)
    set(LIB_EXPORT)
    set(LIB_LOCAL)

    if (NOT ${STATIC_BUILD})
        if (WINDOWS)
            # add dllexport defs

            set(LIB_EXPORT "__declspec (dllexport)")
            set(LIB_LOCAL)

        else()
            # add visibility defs

            set(LIB_EXPORT "__attribute__ ((visibility (\"default\")))")
            set(LIB_LOCAL  "__attribute__ ((visibility (\"hidden\")))")

        endif()
    endif()

    target_compile_definitions(
        ${TARGET}
        PUBLIC
            GLUG_LIB_API=${LIB_EXPORT}
            GLUG_LIB_LOCAL=${LIB_LOCAL}
    )
endfunction()

# define OS variables
macro(detect_os)
    if("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")

        set(GLUG_OS_WIN32 TRUE)

    elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")

        set(GLUG_OS_MACOS TRUE)

    elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")

        set(GLUG_OS_LINUX TRUE)

    elseif ("${CMAKE_SYSTEM_NAME}" STREQUAL "FreeBSD" OR "${CMAKE_SYSTEM_NAME}" STREQUAL "OpenBSD")

        set(GLUG_OS_BSD TRUE)

    endif()
endmacro()
