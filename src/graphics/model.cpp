#include "model.hpp"

#include "texture_utils.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace rockhopper {

void model::draw(rockhopper::shader& shader) {
    for(auto& mesh : meshes) {
        mesh.draw(shader);
    }
}

void model::load_model(std::string path) {
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }

    directory = path.substr(0, path.find_last_of('/'));

    process_node(scene->mRootNode, scene);
}

void model::process_node(aiNode* node, const aiScene* scene) {
    // process all the node's meshes
    for(u32 i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]]; // scene contains all meshes, which are gotten via an index in the node
        meshes.push_back(process_mesh(mesh, scene));
    }

    // continue recursively for node's children
    for(u32 i = 0; i < node->mNumChildren; i++) {
        process_node(node->mChildren[i], scene);
    }
}


mesh model::process_mesh(aiMesh* ai_mesh, const aiScene* scene) {
    std::vector<vertex> vertices;
    std::vector<uint32_t> indices;
    std::vector<texture> textures;

    for(uint32_t i = 0; i < ai_mesh->mNumVertices; i++) {
        vertex vert;
        glm::vec3 vector;
        vector.x = ai_mesh->mVertices[i].x;
        vector.y = ai_mesh->mVertices[i].y;
        vector.z = ai_mesh->mVertices[i].z;
        vert.Position = vector;

        vector.x = ai_mesh->mNormals[i].x;
        vector.y = ai_mesh->mNormals[i].y;
        vector.z = ai_mesh->mNormals[i].z;
        vert.Normal = vector;

        if(ai_mesh->mTextureCoords[0]) {
            glm::vec2 vec;
            vec.x = ai_mesh->mTextureCoords[0][i].x;
            vec.y = ai_mesh->mTextureCoords[0][i].y;
            vert.TexCoords = vec;
        } else {
            vert.TexCoords = glm::vec2(0.0f, 0.0f);
        }

        vertices.push_back(vert);
    }

    // process indices
    for(uint32_t i = 0; i < ai_mesh->mNumFaces; i++) {
        aiFace face = ai_mesh->mFaces[i];
        for(uint32_t j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    // process material
    if(ai_mesh->mMaterialIndex >= 0) {
        aiMaterial* material = scene->mMaterials[ai_mesh->mMaterialIndex];

        std::vector<texture> diffuse_maps = load_material_textures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuse_maps.begin(), diffuse_maps.end());

        std::vector<texture> specular_maps = load_material_textures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specular_maps.begin(), specular_maps.end());
    }

    return mesh(vertices, indices, textures);
}

std::vector<texture> model::load_material_textures(aiMaterial* mat, aiTextureType type, std::string type_name) {
    std::vector<texture> textures;
    for(uint32_t i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);

        bool skip = false;
        for(auto & loaded_texture : textures_loaded) {
            if(std::strcmp(loaded_texture.path.data(), str.C_Str()) == 0) {
                textures.push_back(loaded_texture);
                skip = true;
                break;
            }
        }

        if(!skip) {
            texture tex;
            tex.id = utils::texture_from_file(str.C_Str(), directory, false);
            tex.type = type_name;
            tex.path = str.C_Str();

            textures.push_back(tex);
            textures_loaded.push_back((tex));
        }
    }

    return textures;
}

}