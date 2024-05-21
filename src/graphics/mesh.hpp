#pragma once

#include "glm/glm.hpp"

#include <string>

#include "platform.h"
#include "shader.h"

namespace rockhopper {

struct vertex {
    glm::vec3   Position;
    glm::vec3   Normal;
    glm::vec2   TexCoords;
};

struct texture {
    u32             id;
    std::string     type;
    std::string     path;
};

class mesh {
public:
    std::vector<vertex>     vertices;
    std::vector<u32>         indices;
    std::vector<texture>    textures;

    mesh(std::vector<vertex> vertices, std::vector<u32> indices, std::vector<texture> textures);
    void draw(shader& _shader);

private:
    // render data
    u32 VAO, VBO, EBO;

    void setup_mesh();
};

}