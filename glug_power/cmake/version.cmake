# parse the git tag version in store in the *_VAR variables in the parent scope
# supported git tag versions are in the format %d.%d.%d[-%s]-%d-%s
function (parse_git_tag_version MAJOR_VAR MINOR_VAR PATCH_VAR META_VAR REV_VAR HASH_VAR FULL_VAR)
    # read tag from git
    execute_process(
        COMMAND
            git describe --tag --long
        WORKING_DIRECTORY
            ${CMAKE_CURRENT_SOURCE_DIR}
        OUTPUT_VARIABLE
            VERSION
        ERROR_QUIET
    )

    # set default version values
    set(${MAJOR_VAR} 0       PARENT_SCOPE)
    set(${MINOR_VAR} 0       PARENT_SCOPE)
    set(${PATCH_VAR} 0       PARENT_SCOPE)
    set(${META_VAR}  ""      PARENT_SCOPE)
    set(${REV_VAR}   0       PARENT_SCOPE)
    set(${HASH_VAR}  ""      PARENT_SCOPE)
    set(${FULL_VAR}  "0.0.0-0-" PARENT_SCOPE)

    # the regex to match and parse
    set(VER_REGEX "^([0-9]+).([0-9]+).([0-9]+)-([^-]+)?-?([0-9]+)-(.*)")

    if (VERSION MATCHES ${VER_REGEX})
        string(STRIP ${VERSION} VERSION)
        string(REGEX MATCH ${VER_REGEX} VER_MATCH ${VERSION})

        if (${CMAKE_MATCH_COUNT} GREATER_EQUAL 5)
            list(
                APPEND
                PARSED
                ${CMAKE_MATCH_1}
                ${CMAKE_MATCH_2}
                ${CMAKE_MATCH_3}
                ${CMAKE_MATCH_4}
                ${CMAKE_MATCH_5}
            )

            if (${CMAKE_MATCH_COUNT} EQUAL 6)
                list(APPEND PARSED ${CMAKE_MATCH_6})
            elseif (${CMAKE_MATCH_COUNT} EQUAL 5)
                list(INSERT PARSED 4 "")
            endif()
        else()
            message(DEBUG "the current git tag version is not supported")
            return()
        endif()

        list(GET PARSED 0 PARSED_MAJOR)
        list(GET PARSED 1 PARSED_MINOR)
        list(GET PARSED 2 PARSED_PATCH)
        list(GET PARSED 3 PARSED_META)
        list(GET PARSED 4 PARSED_REV)
        list(GET PARSED 5 PARSED_HASH)

        set(${MAJOR_VAR} ${PARSED_MAJOR} PARENT_SCOPE)
        set(${MINOR_VAR} ${PARSED_MINOR} PARENT_SCOPE)
        set(${PATCH_VAR} ${PARSED_PATCH} PARENT_SCOPE)
        set(${META_VAR}  ${PARSED_META}  PARENT_SCOPE)
        set(${REV_VAR}   ${PARSED_REV}   PARENT_SCOPE)
        set(${HASH_VAR}  ${PARSED_HASH}  PARENT_SCOPE)
        set(${FULL_VAR}  ${VERSION}      PARENT_SCOPE)
    else()
        message(DEBUG "\"git desribe --tags\" didn't return a tag version")
    endif()

endfunction()
