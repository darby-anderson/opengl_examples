//
// Created by darby on 3/4/2023.
//

#pragma once

#include <iostream>

#ifndef GLAD_AND_GLFW
#define GLAD_AND_GLFW
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#endif


#include "platform.h"

namespace rockhopper {

struct WindowConfiguration {
    int width = 0;
    int height = 0;

    cstring name = nullptr;

    GLFWframebuffersizefun framebuffer_size_callback = nullptr;
};

struct Window {

public:
    void init(WindowConfiguration* configuration);
    void shutdown();

    bool shouldClose();
    void setWindowToClose();

    void update();

    GLFWwindow* glfwWindow = nullptr;

    int width = 0;
    int height = 0;

private:
    bool shouldCloseSet = false;

};

}


