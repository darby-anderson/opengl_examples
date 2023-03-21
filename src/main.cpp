//
// Created by darby on 3/2/2023.
//

#include <iostream>

#include "window.h"
#include "input.h"

#ifndef GLAD_AND_GLFW
#define GLAD_AND_GLFW
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#endif


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    std::cout << "Hello OpenGL" << std::endl;

    rockhopper::WindowConfiguration windowConfig{};
    windowConfig.width = 800;
    windowConfig.height = 600;
    windowConfig.name = "Rockhopper Window";
    windowConfig.framebuffer_size_callback = framebuffer_size_callback;

    rockhopper::Window window;
    window.init(&windowConfig);

    rockhopper::input input;
    input.init(&window);

    while(!window.shouldClose()) {
        // update window, this includes the input
        glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window.glfwWindow);
        glfwPollEvents();

        input.new_frame();

        if(input.is_key_down(rockhopper::KEY_E)) {
            std::cout << "The E key is down" << std::endl;
        }

    }

    glfwTerminate();

    return 0;
}