# define OS variables
function(detect_os IS_WIN IS_OSX IS_LIN IS_BSD)
    set(WIN FALSE)
    set(OSX FALSE)
    set(LIN FALSE)
    set(BSD FALSE)

    if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")

        set(WIN TRUE)

    elseif ("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")

        set(OSX TRUE)

    elseif ("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")

        set(LIN TRUE)

    elseif ("${CMAKE_SYSTEM_NAME}" STREQUAL "FreeBSD" OR "${CMAKE_SYSTEM_NAME}" STREQUAL "OpenBSD")

        set(BSD TRUE)

    endif()

    set(${IS_WIN} ${WIN} PARENT_SCOPE)
    set(${IS_OSX} ${OSX} PARENT_SCOPE)
    set(${IS_LIN} ${LIN} PARENT_SCOPE)
    set(${IS_BSD} ${BSD} PARENT_SCOPE)
endfunction()
