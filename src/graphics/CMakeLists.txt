cmake_minimum_required(VERSION 3.20)

add_library(
        graphics
        "shader.h"
        "shader.cpp"
        "mesh.hpp"
        "mesh.cpp"
        "model.hpp"
        "model.cpp"
        "pipelines.hpp"
        "pipelines.cpp"
        "texture_utils.hpp"
        "texture_utils.cpp"
)

target_include_directories(graphics PUBLIC "${PROJECT_SOURCE_DIR}/deps/stb")

target_link_libraries(graphics core)
target_include_directories(graphics PUBLIC "${PROJECT_SOURCE_DIR}/src/core")

target_link_libraries(graphics glad)
target_link_libraries(graphics glm::glm)

target_link_libraries(graphics assimp)
target_include_directories(graphics PUBLIC "${PROJECT_SOURCE_DIR}/deps/assimp/include")
