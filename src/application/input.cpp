//
// Created by darby on 3/5/2023.
//

#include <cstring>

#include <GLFW/glfw3.h>

#include "input.h"

namespace rockhopper {


    void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        input* inputHandle = static_cast<input*>(glfwGetWindowUserPointer(window));

        if(action == GLFW_PRESS) {
            inputHandle->keys[key] = 1;
        }
    }

    void input::init(Window* window) {
        this->window = window;

        glfwSetWindowUserPointer(this->window->windowHandle, reinterpret_cast<void*>(this));

        memset(keys, 0, KEY_COUNT);
        memset(previous_keys, 0, KEY_COUNT);
    }

    void input::new_frame() {
        for(u32 i = 0; i < KEY_COUNT; i++) {
            previous_keys[i] = keys[i];
        }
    }

    bool input::is_key_down(Key key) {
        return keys[key] && has_focus();
    }

    bool input::is_key_just_pressed(Key key) {
        return keys[key] && !previous_keys[key] && has_focus();
    }

    bool input::is_key_just_released(Key key) {
        return !keys[key] && previous_keys[key] && has_focus();
    }

    bool input::has_focus() {
        glfwGetWindowAttrib(window->windowHandle, GLFW_FOCUSED);
    }
}