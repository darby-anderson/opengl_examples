//
// Created by darby on 3/4/2023.
//

#pragma once

#include <iostream>

#include <GLFW/glfw3.h>

#include "platform.h"

namespace rockhopper {

struct WindowConfiguration {
    int width = 0;
    int height = 0;

    cstring name = nullptr;

    GLFWframebuffersizefun framebuffer_size_callback;
    // void(*framebuffer_size_callback_2) (GLFWwindow*, int, int);

    void process_input(GLFWwindow* window);
};

struct Window {

public:
    void init(WindowConfiguration* configuration);
    void shutdown();

    bool shouldClose();
    void setWindowToClose();

    void update();

    GLFWwindow* windowHandle;

    int width;
    int height;

private:
    bool shouldCloseSet = false;

};

}


