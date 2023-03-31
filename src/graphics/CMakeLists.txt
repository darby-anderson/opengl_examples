cmake_minimum_required(VERSION 3.20)

add_library(
        graphics
        "shader.h"
        "shader.cpp"
)

target_link_libraries(graphics core)
target_include_directories(graphics PUBLIC "${PROJECT_SOURCE_DIR}/src/core")

target_link_libraries(graphics glad)