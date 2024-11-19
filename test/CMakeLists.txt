link_libraries(RCore)

project(RCoreTest)
add_executable(
    ${PROJECT_NAME}
    a.c
)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})