cmake_minimum_required(VERSION 3.0.0)
project(hello_window VERSION 1.0.0)
cmake_policy(SET CMP0072 NEW)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

add_executable(hello_window
    src/config.h
    src/config.cpp
    src/main.cpp
    src/glad.c
    src/systems/camera_system.cpp
    src/systems/motion_system.cpp
    src/systems/render_system.cpp
    src/view/shader.cpp
    src/controller/app.cpp
)

target_include_directories(hello_window PRIVATE includes)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(links/glfw)
target_link_libraries(hello_window glfw OpenGL::GL)
