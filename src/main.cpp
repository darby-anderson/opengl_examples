//
// Created by darby on 3/2/2023.
//

#include <iostream>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "window.h"
#include "input.h"
#include "shader.h"
#include "memory.h"
#include "camera.h"
#include "texture_helpers.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

const u32 SCR_WIDTH = 800;
const u32 SCR_HEIGHT = 600;

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

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

    rockhopper::InputConfiguration inputConfig {};
    inputConfig.window = &window;

    rockhopper::input input = {};
    input.init(&inputConfig);

    rockhopper::shader cube_shader = {};
    cube_shader.init("../shaders/basic_lighting/cube.vert", "../shaders/basic_lighting/cube.frag");

    rockhopper::shader light_shader = {};
    light_shader.init("../shaders/basic_lighting/light.vert", "../shaders/basic_lighting/light.frag");

    float vertices[] = {
            // positions          // normals           // texture coords
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };


    /* -- VAO --
     * A VAO stores vertex attribute calls, so they only need to be called once.
     * It stores:   - calls to glEnableVertexAttribArray or glDisableVertexAttribArray
     *              - vertex attrib configurations via glVertexAttribPointer
     *              - vertex buffer objects associated with vertex attributes by calls to glVertexAttribPointer
     * After storing, only the VAO needs to be bound
     */

    u32 VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO); // associates buffer object with a buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);

    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // texture coords
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // configure light's VAO
    u32 lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) nullptr);
    glEnableVertexAttribArray(0);

    // Material
    cube_shader.use();
    cube_shader.setInt("material.diffuse", 0);
    cube_shader.setInt("material.specular", 1);
    cube_shader.setFloat("material.shininess", 32.0f);

    // Light
    cube_shader.setFloatVec3("light.position", lightPos);
    cube_shader.setFloatVec3("light.ambient", 0.2f, 0.2f, 0.2f);
    cube_shader.setFloatVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
    cube_shader.setFloatVec3("light.specular", 1.0f, 1.0f, 1.0f);

    rockhopper::camera cam;
    { // don't want these vec3s escaping context
        auto cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
        auto cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
        cam.init(cameraPos, cameraUp);
    }

    u32 diffuse_map_texture = rockhopper::load_texture("../assets/textures/container2.png");
    u32 specular_map_texture = rockhopper::load_texture("../assets/textures/container2_specular.png");

    glEnable(GL_DEPTH_TEST);

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    while(!window.shouldClose()) {
        auto currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        input.start_new_frame(); // must be called before glfwPollEvents
        glfwPollEvents();
        cam.processInput(&input, deltaTime);

        // update window, this includes the input
        glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cube_shader.use();
        cube_shader.setFloatVec3("view_pos", cam.position);
        // Light
        cube_shader.setFloatVec3("light.position", lightPos);

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(cam.zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = cam.get_view_matrix();
        cube_shader.setFloatMatrix4("projection", projection);
        cube_shader.setFloatMatrix4("view", view);

        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        cube_shader.setFloatMatrix4("model", model);

        // render the cube
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuse_map_texture);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specular_map_texture);

        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // also draw the lamp object
        light_shader.use();
        light_shader.setFloatVec3("light_color", 1.0f, 1.0f, 1.0f);
        light_shader.setFloatMatrix4("projection", projection);
        light_shader.setFloatMatrix4("view", view);

        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2));
        light_shader.setFloatMatrix4("model", model);

        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window.glfwWindow);
    }

    glfwTerminate();

    return 0;
}