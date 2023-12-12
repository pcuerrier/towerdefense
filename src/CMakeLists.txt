set(BINARY ${CMAKE_PROJECT_NAME})

find_package(OpenGL REQUIRED)

set(SOURCES
    config.cpp
    main.cpp
    glad.c
    controller/app.cpp
    controller/entity_manager.cpp
    systems/camera_system.cpp
    systems/motion_system.cpp
    systems/render_system.cpp
    view/shader.cpp
)

add_executable(${BINARY}_run ${SOURCES})
add_library(${BINARY}_lib STATIC ${SOURCES})

message(PROJECT_SOURCE_DIR="${CMAKE_CURRENT_LIST_DIR}")

target_include_directories(${BINARY}_run PUBLIC ${CMAKE_SOURCE_DIR}/includes)
target_include_directories(${BINARY}_lib PUBLIC ${CMAKE_SOURCE_DIR}/includes)

target_link_libraries(${BINARY}_run PUBLIC glfw OpenGL::GL)
target_link_libraries(${BINARY}_lib PUBLIC glfw OpenGL::GL)
