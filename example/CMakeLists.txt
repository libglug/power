include(${PROJECT_SOURCE_DIR}/cmake/macros/add_example.cmake)

set(GLUG_TARGET_NAME ${CMAKE_PROJECT_NAME}_test)

add_example(
    TARGET_NAME ${GLUG_TARGET_NAME}
)

install(
    TARGETS ${GLUG_TARGET_NAME}
    DESTINATION ${GLUG_DIST_XMPL_DIR}
)
