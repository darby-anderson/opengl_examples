cmake_minimum_required(VERSION 3.20)

add_library(
        application
        "window.h"
        "window.cpp"
        "keys.h"
        "input.h"
        "input.cpp"
        "camera.h"
        "scenes.hpp"
        "scenes.cpp"
)

target_link_libraries(application core)
target_include_directories(application PUBLIC "${PROJECT_SOURCE_DIR}/src/core")

target_link_libraries(application graphics)
target_include_directories(application PUBLIC "${PROJECT_SOURCE_DIR}/src/graphics")

target_link_libraries(application glfw)
target_link_libraries(application glad)