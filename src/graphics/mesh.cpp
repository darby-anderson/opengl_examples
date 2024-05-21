#include "mesh.hpp"

namespace rockhopper {

    mesh::mesh(std::vector<vertex> vertices, std::vector<u32> indices, std::vector<texture> textures) {
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;

        setup_mesh();
    }

    void mesh::setup_mesh() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(u32), &indices[0], GL_STATIC_DRAW);

        // vertex positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);
        // vertex normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*) offsetof(vertex, Normal));
        // vertex texture coords
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, TexCoords));

        glBindVertexArray(0);
    }

    void mesh::draw(shader& shader) {

        u32 diffuseNr = 1;
        u32 specularNr = 1;

        for(u32 i = 0; i < textures.size(); i++) {
            glActiveTexture(GL_TEXTURE0 + i); // activate correct texture unit before binding

            std::string number;
            std::string name = textures[i].type;

            if(name == "texture_diffuse") {
                number = std::to_string(diffuseNr++);
            } else if(name == "texture_specular") {
                number = std::to_string(specularNr++);
            }

            std::string texture_name = std::string("material.").append(name).append(number);
            shader.setInt(texture_name, i);
            glBindTexture(GL_TEXTURE_2D, textures[i].id);
        }

        glActiveTexture(GL_TEXTURE0);

        // draw mesh
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

}