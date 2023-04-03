//
// Created by darby on 3/2/2023.
//

#include <iostream>
#include <cmath>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "window.h"
#include "input.h"
#include "shader.h"
#include "memory.h"

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

    rockhopper::input input = {};
    input.init(&window);

    float vertices[] = {
            // positions                        // colors                   // texture coords
            0.5f, 0.5f, 0.0f,       1.0f, 0.0f, 0.0f,   1.0f, 1.0f,                                                  // top right
            0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,   1.0f, 0.0f,                                                    // bottom right
            -0.5f,  -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f,                                                 // bottom left
            -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f,                                                  // top left
    };

    int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    float texCoords[] = {
            0.0f, 0.0f,
            1.0f, 0.0f,
            0.5f, 1.0f
    };

    u32 EBO;
    glGenBuffers(1, &EBO);

    u32 VBO;
    // glGenBuffers returns n buffer object names in buffers
    // These names are not associated with buffers until glBindBuffer
    // (GLsizei n, GLuint* buffers)
    glGenBuffers(1, &VBO);

    // A VAO stores vertex attribute calls, so they only need to be called once.
    // It stores:   - calls to glEnableVertexAttribArray or glDisableVertexAttribArray
    //              - vertex attrib configurations via glVertexAttribPointer
    //              - vertex buffer objects associated with vertex attributes by calls to glVertexAttribPointer
    // After storing, only the VAO needs to be bound
    u32 VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Binds a buffer object to the specified buffer binding point (u32 handle)
    // (GLenum target, GLuint buffer)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Creates a new data store for a buffer object. The buffer object currently bound to target is used
    // (GLenum target, GLsizeiptr size, const void* data, GLenum usage)
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Specifies the location and data format of the array of generic vertex attributes at index index to use when rendering
    // (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)
    glVertexAttribPointer(2, 8, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    // Enables the generic vertex attribute array specified by index
    // (GLuint index)
    glEnableVertexAttribArray(2);

    rockhopper::shader shader = {};
    shader.init("../shaders/texture.vert", "../shaders/texture.frag");

    // Load Texture Image
    int width, height, nrChannels;
    const char* texturePath = "../assets/textures/container.jpg";
    unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, 0);

    if(!data) {
        std::cout << "error loading texture at [" << texturePath << "]" << std::endl;
        return 1;
    }

    // TEXTURE
    u32 texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Texture settings
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    while(!window.shouldClose()) {
        input.start_new_frame();

        // update window, this includes the input
        glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();

        /*double timeValue = glfwGetTime();
        float greenValue = static_cast<float>(sin(timeValue) / 2.0 + 0.5);
        shader.setFloat("greenColor", greenValue);*/

        // int vertexColorLocation = glGetUniformLocation(shader.ID, "greenColor");
        // glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

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