# create simple example with simple dependencies
function (add_example)
    set(OPTIONS)
    set(SINGLE_VALS TARGET_NAME INSTALL_PATH)
    set(MULTI_VALS SRC LINK_LIBS)
    cmake_parse_arguments(GLUG "${OPTIONS}" "${SINGLE_VALS}" "${MULTI_VALS}" ${ARGN})

    add_executable(${GLUG_TARGET_NAME} ${PLATFORM} ${GLUG_SRC})
    target_link_libraries(${GLUG_TARGET_NAME} ${GLUG_LINK_LIBS})

    set_target_properties(
        ${GLUG_TARGET_NAME}
        PROPERTIES
            INSTALL_RPATH "$ORIGIN;@loader_path"
            BUILD_WITH_INSTALL_RPATH TRUE
    )

    install(
        TARGETS
            ${GLUG_TARGET_NAME}
        DESTINATION
            ${GLUG_INSTALL_PATH}
    )
endfunction()
