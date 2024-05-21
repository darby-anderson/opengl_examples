//
// Created by darby on 5/19/2024.
//

#include "texture_utils.hpp"

namespace rockhopper::utils
{

uint32_t texture_from_file(cstring path, const std::string& directory, bool gamma) {
    std::string file_name = std::string(path);
    file_name = directory + '/' + file_name;

    uint32_t textureID;
    glGenTextures(1, &textureID);

    int width, height, nr_components;
    uint8_t* data = stbi_load(file_name.c_str(), &width, &height, &nr_components, 0);
    if(data) {
        GLenum format;
        if(nr_components == 1) {
            format = GL_RED;
        } else if(nr_components == 3) {
            format = GL_RGB;
        } else if(nr_components == 4) {
            format = GL_RGBA;
        }

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    } else {
        std::cout << "Error: texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
}
