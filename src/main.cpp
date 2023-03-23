//
// Created by darby on 3/2/2023.
//

#include <iostream>

#include "window.h"
#include "input.h"

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

    float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f
    };


    u32 VBO;
    // glGenBuffers returns n buffer object names in buffers
    // These names are not associated with buffers until glBindBuffer
    // (GLsizei n, GLuint* buffers)
    glGenBuffers(1, &VBO);

    // Binds a buffer object to the specified buffer binding point (u32 handle)
    // (GLenum target, GLuint buffer)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Creates a new data store for a buffer object. The buffer object currently bound to target is used
    // (GLenum target, GLsizeiptr size, const void* data, GLenum usage)
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    u32 vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);




    while(!window.shouldClose()) {
        input.start_new_frame();

        // update window, this includes the input
        glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window.glfwWindow);
        glfwPollEvents();

        if(input.is_key_just_pressed(rockhopper::KEY_E)) {
            std::cout << "The E key was just pressed" << std::endl;
        }

        if(input.is_key_down(rockhopper::KEY_E)) {
            std::cout << "The E key is down" << std::endl;
        }

        if(input.is_key_just_released(rockhopper::KEY_E)) {
            std::cout << "The E key was just released" << std::endl;
        }
    }

    glfwTerminate();

    return 0;
}