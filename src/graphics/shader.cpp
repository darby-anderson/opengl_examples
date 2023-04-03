//
// Created by darby on 3/22/2023.
//

#include "shader.h"

#include "file_system.h"

namespace rockhopper {

    void shader::init(cstring vertexPath, cstring fragmentPath) {

        Allocator* systemAllocator = &MemoryService::instance()->system_allocator;

        // 1. retrieve the vertex/fragment source code from file path
        FileReadResult vertexReadResult = file_read_text(vertexPath, systemAllocator);
        if(vertexReadResult.size == 0) {
            std::string err = std::string("Error reading from vertex shader at: ") + vertexPath;
            throw std::runtime_error(err);
        }

        FileReadResult fragmentReadResult = rockhopper::file_read_text(fragmentPath, systemAllocator);
        if(fragmentReadResult.size == 0) {
            std::string err = std::string("Error reading from fragment shader at: ") + fragmentPath;
            throw std::runtime_error(err);
        }

        /*std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // ensure ifstream objects throw exceptions
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try {
            // open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close all file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        } catch(std::ifstream::failure e) {
            std::cout << "ERROR::SHADER::FILE NOT SUCCESSFULLY READ" << std::endl;
        }
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();*/

        // 2. compile shaders
        u32 vertex, fragment;
        int success;
        char infoLog[512];

        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vertexReadResult.data, NULL);
        glCompileShader(vertex);

        // print compile errors if any
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION FAILED" << std::endl << infoLog << std::endl;
        }

        // fragment shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fragmentReadResult.data, NULL);
        glCompileShader(fragment);

        // print compile errors if any
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION FAILED" << std::endl << infoLog << std::endl;
        }

        // Shader program
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);

        // print linking errors if any
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(ID, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING FAILED" << std::endl << infoLog << std::endl;
        }

        // delete the shaders as they're linked into our program now and are no longer needed
        glDeleteShader(vertex);
        glDeleteShader(fragment);

        systemAllocator->deallocate(vertexReadResult.data);
        systemAllocator->deallocate(fragmentReadResult.data);
    }

    void shader::use() {
        glUseProgram(ID);
    }

    void shader::setBool(const std::string& name, bool value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }

    void shader::setInt(const std::string& name, int value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }

    void shader::setFloat(const std::string& name, float value) const {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }

}