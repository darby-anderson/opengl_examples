#include "scenes.hpp"

#include <map>

namespace rockhopper {

const u32 SCR_WIDTH = 800;
const u32 SCR_HEIGHT = 600;

void run_stencil_outline_scene(Window& window, Input& input) {
    shader model_shader = {};
    model_shader.init("../shaders/stencil_buffer_outline/normal_draw.vert", "../shaders/stencil_buffer_outline/normal_draw.frag");

    shader outline_shader = {};
    outline_shader.init("../shaders/stencil_buffer_outline/normal_draw.vert", "../shaders/stencil_buffer_outline/outline.frag");

    stbi_set_flip_vertically_on_load(true);

    glEnable(GL_DEPTH_TEST);

    model bag_model("../assets/models/backpack/backpack.obj");

    camera cam;
    { // don't want these vec3s escaping context
        auto cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
        auto cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
        cam.init(cameraPos, cameraUp);
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    while(!window.shouldClose()) {
        auto currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        input.start_new_frame(); // must be called before glfwPollEvents
        glfwPollEvents();
        cam.processInput(&input, deltaTime);

        // Set stencil functions
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

        // update window, this includes the input
        glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        // draw normal model
        glStencilMask(0x00); // No update to the stencil mask
        model_shader.use();

        glm::mat4 projection = glm::perspective(glm::radians(cam.zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = cam.get_view_matrix();

        pipelines::init_basic_mvp_model(model_shader, view, projection);

        glm::vec3 translation = glm::vec3 (0.0f, 0.0f, 0.0f);
        glm::vec3 scale = glm::vec3 (1.0f, 1.0f, 1.0f);
        pipelines::draw_basic_mvp_model(model_shader, bag_model, translation, scale);

        // Draw model, and set xFF in stencil
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilMask(0xFF);

        translation = glm::vec3 (5.0f, 0.0f, 0.0f);
        pipelines::draw_basic_mvp_model(model_shader, bag_model, translation, scale);

        bag_model.draw(model_shader);

        // Draw outline of model above
        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilMask(0x00);

        outline_shader.use();

        pipelines::init_basic_mvp_model(outline_shader, view, projection);

        translation = glm::vec3(5.0f, 0.0f, 0.0f);
        scale = glm::vec3(0.97f, 0.97f, 0.97f);
        pipelines::draw_basic_mvp_model(outline_shader, bag_model, translation, scale);

        glStencilMask(0xFF);
        glStencilFunc(GL_ALWAYS, 1, 0xFF);

        glfwSwapBuffers(window.glfwWindow);
    }

    glfwTerminate();
}

void run_blend_scene(Window& window, Input& input) {
// configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // build and compile shaders
    // -------------------------
    shader blending_shader {};
    blending_shader.init("../shaders/blending/blend.vert", "../shaders/blending/blend.frag");

    shader transparent_shader {};
    transparent_shader.init("../shaders/transparency/transparency.vert", "../shaders/transparency/transparency.frag");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float cubeVertices[] = {
            // positions          // texture Coords
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    float planeVertices[] = {
            // positions          // texture Coords
            5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
            -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
            -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

            5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
            -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
            5.0f, -0.5f, -5.0f,  2.0f, 2.0f
    };
    float transparentVertices[] = {
            // positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
            0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
            0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
            1.0f, -0.5f,  0.0f,  1.0f,  1.0f,

            0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
            1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
            1.0f,  0.5f,  0.0f,  1.0f,  0.0f
    };

    // cube VAO
    unsigned int cubeVAO, cubeVBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    // plane VAO
    unsigned int planeVAO, planeVBO;
    glGenVertexArrays(1, &planeVAO);
    glGenBuffers(1, &planeVBO);
    glBindVertexArray(planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    // transparent VAO
    unsigned int transparentVAO, transparentVBO;
    glGenVertexArrays(1, &transparentVAO);
    glGenBuffers(1, &transparentVBO);
    glBindVertexArray(transparentVAO);
    glBindBuffer(GL_ARRAY_BUFFER, transparentVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(transparentVertices), transparentVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glBindVertexArray(0);

    // load textures
    // -------------
    cstring texture_directory = "../assets/textures/";
    uint32_t cube_texture = utils::texture_from_file("marble.jpg", texture_directory, true);
    uint32_t floor_texture = utils::texture_from_file("metal.png", texture_directory, true);
    uint32_t transparent_texture = utils::texture_from_file("blending_transparent_window.png", texture_directory, true);
    uint32_t grass_texture = utils::texture_from_file("grass.png", texture_directory, true);

    // transparent window locations
    // --------------------------------
    std::vector<glm::vec3> windows
    {
            glm::vec3(-1.5f, 0.0f, -0.48f),
            glm::vec3( 1.5f, 0.0f, 0.51f),
            glm::vec3( 0.0f, 0.0f, 0.7f),
            glm::vec3(-0.3f, 0.0f, -2.3f),
            glm::vec3( 0.5f, 0.0f, -0.6f)
    };

    std::vector<glm::vec3> vegetation
    {
            glm::vec3(-2.0f, 0.0f, -0.7f),
            glm::vec3( 2.0f, 0.0f, 0.7f),
            glm::vec3( 1.0f, 0.0f, 0.62f),
            glm::vec3(-0.8f, 0.0f, -2.5f),
            glm::vec3 (01.5f, 0.0f, -1.9f)
    };

    // blending_shader configuration
    // --------------------
    blending_shader.setInt("texture1", 0);

    // blending_shader configuration
    // --------------------
    transparent_shader.setInt("texture1", 0);

    camera cam;
    { // don't want these vec3s escaping context
        auto cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
        auto cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
        cam.init(cameraPos, cameraUp);
    }

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    // render loop
    // -----------
    while (!window.shouldClose())
    {
        auto currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        input.start_new_frame(); // must be called before glfwPollEvents
        glfwPollEvents();
        cam.processInput(&input, deltaTime);

        // sort the transparent windows before rendering
        // ---------------------------------------------
        std::map<float, glm::vec3> sorted;
        for (auto window : windows)
        {
            float distance = glm::length(cam.position - window);
            sorted[distance] = window;
        }

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 projection = glm::perspective(glm::radians(cam.zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = cam.get_view_matrix();

        // draw transparent shader objects
        transparent_shader.use();
        pipelines::init_basic_raw_data(transparent_shader, view, projection);
        pipelines::set_instancing_data_basic_raw_data(transparentVAO, grass_texture);

        for(auto translation : vegetation) {
            glm::vec3 scale = glm::vec3(1.0);
            pipelines::draw_basic_raw_data(transparent_shader, 6, translation, scale);
        }

        // draw blending shader objects
        blending_shader.use();
        pipelines::init_basic_raw_data(blending_shader, view, projection);

        // cubes
        pipelines::set_instancing_data_basic_raw_data(cubeVAO, cube_texture);

        glm::vec3 translation = glm::vec3(-1.0f, 0.0f, -1.0f);
        glm::vec3 scale = glm::vec3(1.0);
        pipelines::draw_basic_raw_data(blending_shader, 36, translation, scale);


        translation = glm::vec3(2.0f, 0.0f, 0.0f);
        scale = glm::vec3(1.0);
        pipelines::draw_basic_raw_data(blending_shader, 36, translation, scale);

        // floor
        pipelines::set_instancing_data_basic_raw_data(planeVAO, floor_texture);

        translation = glm::vec3(2.0f, 0.0f, 0.0f);
        scale = glm::vec3(1.0);
        pipelines::draw_basic_raw_data(blending_shader, 6, translation, scale);

        // windows (from furthest to nearest)
        pipelines::set_instancing_data_basic_raw_data(transparentVAO, transparent_texture);

        for (std::map<float, glm::vec3>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); ++it)
        {
            translation = it->second;
            scale = glm::vec3(1.0);
            pipelines::draw_basic_raw_data(blending_shader, 6, translation, scale);
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window.glfwWindow);
        // glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &planeVAO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteBuffers(1, &planeVBO);

    glfwTerminate();
}

}