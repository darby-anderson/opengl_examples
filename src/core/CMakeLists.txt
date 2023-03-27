cmake_minimum_required(VERSION 3.20)

add_library(
        core
        "platform.h"
        "file_system.h"
        "file_system.cpp"
        "memory.h"
        "memory.cpp"
        "service.h"
)

target_link_libraries(core tlsf)

set(IMGUI_DIR ../../deps/imgui)
include_directories(${IMGUI_DIR} ${IMGUI_DIR}/backends)
target_sources(${PROJECT_NAME} PRIVATE
        ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        )