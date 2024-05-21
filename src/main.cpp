//
// Created by darby on 3/2/2023.
//

#include <iostream>

#include "window.h"
#include "input.h"
#include "memory.h"
#include "scenes.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {

    std::cout << "Hello OpenGL" << std::endl;

    rockhopper::MemoryServiceConfiguration memConfig{};
    memConfig.maximum_dynamic_size = rock_mega(32);
    rockhopper::MemoryService* memoryService = rockhopper::MemoryService::instance();
    memoryService->init(&memConfig);

    rockhopper::WindowConfiguration windowConfig{};
    windowConfig.width = 800;
    windowConfig.height = 600;
    windowConfig.name = "Rockhopper Window";
    windowConfig.framebuffer_size_callback = framebuffer_size_callback;

    rockhopper::Window window;
    window.init(&windowConfig);

    rockhopper::InputConfiguration inputConfig{};
    inputConfig.window = &window;

    rockhopper::Input input = {};
    input.init(&inputConfig);

    // rockhopper::run_stencil_outline_scene(window, input);

    rockhopper::run_blend_scene(window, input);

    return 0;
}
