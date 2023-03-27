cmake_minimum_required(VERSION 3.20)
project(OpenGL)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME} src/main.cpp src/graphics/shader.cpp src/graphics/shader.h)

# dependencies

# GLFW - https://www.glfw.org/docs/latest/build_guide.html#build_link_cmake_source
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(deps/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

# GLM - https://github.com/g-truc/glm/blob/master/manual.md#-15-finding-glm-with-cmake
add_subdirectory(deps/glm)
target_link_libraries(${PROJECT_NAME} glm::glm)

# IMGUI - https://github.com/ocornut/imgui/blob/master/examples/example_glfw_vulkan/CMakeLists.txt
set(IMGUI_DIR deps/imgui)
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

# STB
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/deps/stb)

# GLAD
add_subdirectory(deps/glad)
target_link_libraries(${PROJECT_NAME} glad)

# TLSF
add_subdirectory(deps/tlsf)
target_link_libraries(${PROJECT_NAME} tlsf)

# OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} opengl32)

# Our libraries
add_subdirectory(src/core)
target_link_libraries(${PROJECT_NAME} core)
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/src/core")

add_subdirectory(src/graphics)
target_link_libraries(${PROJECT_NAME} graphics)
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/src/graphics")

add_subdirectory(src/application)
target_link_libraries(${PROJECT_NAME} application)
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/src/application")
