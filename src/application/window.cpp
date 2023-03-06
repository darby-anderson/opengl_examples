//
// Created by darby on 3/4/2023.
//

#include "window.h"


namespace rockhopper {

    void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    }

    void Window::init(WindowConfiguration* config) {

        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        windowHandle =  glfwCreateWindow(800, 600, "OpenGL Examples", nullptr, nullptr);

        if(windowHandle == nullptr) {
            cstring err = "Failed to create OpenGL context";
            std::cout << err << std::endl;
            glfwTerminate();
            throw std::runtime_error(err);
        }

        glViewport(0, 0, config->width, config->height);
        glfwSetFramebufferSizeCallback(windowHandle, config->framebuffer_size_callback);

    }

    void Window::shutdown() {
        glfwTerminate();
    }

    void Window::setWindowToClose() {
        shouldCloseSet = true;
    }

    bool Window::shouldClose() {
        return glfwWindowShouldClose(windowHandle) || shouldCloseSet;
    }

    void Window::update() {

    }


}

