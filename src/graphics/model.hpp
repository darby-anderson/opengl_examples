#pragma once

#include <string>

#include "stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "shader.h"
#include "mesh.hpp"
#include <glad/glad.h>
#include "platform.h"
#include <iostream>


namespace rockhopper {

class model {
public:
    model(char* path) {
        load_model(path);
    }
    void draw(shader& shader);

private:
     std::vector<texture> textures_loaded;
     std::vector<mesh> meshes;
     std::string directory;

     void load_model(std::string path);
     void process_node(aiNode *node, const aiScene* scene);
     mesh process_mesh(aiMesh* ai_mesh, const aiScene* scene);
     std::vector<texture> load_material_textures(aiMaterial* mat, aiTextureType type, std::string type_name);

};


}