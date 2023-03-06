//
// Created by darby on 3/2/2023.
//

#include <iostream>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "window.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window, true);
    }
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

    int version = gladLoadGL(glfwGetProcAddress);
    if(version == 0) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        glfwTerminate();
        return -1;
    }

    while(!window.shouldClose()) {
        // update window, this includes the input


    }

    while(!glfwWindowShouldClose(window)) {
        process_input(window);

        // rendering commands
        glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}