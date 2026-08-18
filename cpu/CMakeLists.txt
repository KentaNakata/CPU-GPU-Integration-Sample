CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

project("project_cpu" CXX)
set(PROJECT_VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 20)

set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")

add_subdirectory("${SOURCE_DIR}/Common")
add_subdirectory("${SOURCE_DIR}/Main")
