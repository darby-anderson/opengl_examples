//
// Created by darby on 3/22/2023.
//

#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "platform.h"


namespace rockhopper {

struct shader {

public:
    // the program id
    u32 ID;

    // and reads a builds the shader
    void init(const char* vertexPath, const char* fragmentPath);

    // activate the shader
    void use();

    // utility uniform functions
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;


};

}
