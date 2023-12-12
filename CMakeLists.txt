cmake_minimum_required(VERSION 3.20.0)
project(hello_window VERSION 0.0.1 LANGUAGES CXX)
cmake_policy(SET CMP0072 NEW)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(src)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(ROOT_DIR ${CMAKE_SOURCE_DIR})

add_subdirectory(lib/glfw)
add_subdirectory(lib/googletest)
add_subdirectory(src)
add_subdirectory(tests)
