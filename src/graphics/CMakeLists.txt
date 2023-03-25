cmake_minimum_required(VERSION 3.20)

add_library(
        graphics
        "shader.h"
        "shader.cpp"
)

target_link_libraries(graphics glad)