//
// Created by darby on 3/5/2023.
//

#include <cstring>

#include "input.h"

namespace rockhopper {

    void scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
        auto inputHandle = static_cast<Input*>(glfwGetWindowUserPointer(window));
        inputHandle->on_scroll((f32)xOffset, (f32)yOffset);
    }

    void mouseCallback(GLFWwindow* window, double xPos, double yPos) {
        auto inputHandle = static_cast<Input*>(glfwGetWindowUserPointer(window));
        inputHandle->on_mouse_move((f32)xPos, (f32)yPos);
    }

    void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
        auto inputHandle = static_cast<Input*>(glfwGetWindowUserPointer(window));

        if(action == GLFW_PRESS) {
            inputHandle->mouse_buttons[button] = 1;
            inputHandle->first_frame_mouse_buttons[button] = 1;
        } else if(action == GLFW_RELEASE) {
            inputHandle->mouse_buttons[button] = 0;
            inputHandle->released_mouse_buttons[button] = 1;
        }
    }

    void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        auto inputHandle = static_cast<Input*>(glfwGetWindowUserPointer(window));

        if(action == GLFW_PRESS) {
            inputHandle->keys[key] = 1;
            inputHandle->first_frame_keys[key] = 1;
        } else if(action == GLFW_RELEASE) {
            inputHandle->keys[key] = 0;
            inputHandle->released_keys[key] = 1;
        }
    }

    void Input::init(InputConfiguration* input_configuration) {
        this->window = input_configuration->window;

        glfwSetInputMode(this->window->glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        glfwSetWindowUserPointer(this->window->glfwWindow, reinterpret_cast<void*>(this));
        glfwSetKeyCallback(this->window->glfwWindow, keyCallback);
        glfwSetMouseButtonCallback(this->window->glfwWindow, mouseButtonCallback);
        glfwSetCursorPosCallback(this->window->glfwWindow, mouseCallback);
        glfwSetScrollCallback(this->window->glfwWindow, scrollCallback);

        memset(keys, 0, KEY_COUNT);
        memset(first_frame_keys, 0, KEY_COUNT);
        memset(released_keys, 0, KEY_COUNT);

        memset(mouse_buttons, 0, MOUSE_BUTTON_COUNT);
        memset(first_frame_mouse_buttons, 0, MOUSE_BUTTON_COUNT);
        memset(released_mouse_buttons, 0, MOUSE_BUTTON_COUNT);
    }

    void Input::start_new_frame() {
        for(u32 i = 0; i < KEY_COUNT; i++) {
            released_keys[i] = 0;
            first_frame_keys[i] = 0;
        }

        for(u32 i = 0; i < MOUSE_BUTTON_COUNT; i++) {
            released_mouse_buttons[i] = 0;
            first_frame_mouse_buttons[i] = 0;
        }

        mouse_move_data.has_moved = false;
        scroll_data.has_scrolled = false;
    }

    void Input::on_scroll(f32 x_offset, f32 y_offset) {
        scroll_data.has_scrolled = true;

        scroll_data.x_offset = x_offset;
        scroll_data.y_offset = y_offset;
    }

    ScrollData Input::get_scroll_info_this_frame() {
        return scroll_data;
    }

    void Input::on_mouse_move(f32 new_position_x, f32 new_position_y) {
        mouse_move_data.has_moved = true;

        if(!has_ever_received_mouse_data) {
            has_ever_received_mouse_data = true;

            mouse_move_data.previous_x_position = new_position_x;
            mouse_move_data.previous_y_position = new_position_y;
        } else {
            mouse_move_data.previous_x_position = mouse_move_data.x_position;
            mouse_move_data.previous_y_position = mouse_move_data.y_position;
        }

        mouse_move_data.x_position = new_position_x;
        mouse_move_data.y_position = new_position_y;
    }

    MouseMoveData Input::get_mouse_move_info_this_frame() {
        return mouse_move_data;
    }

    bool Input::is_key_down(Key key) {
        return keys[key] && has_focus();
    }

    bool Input::is_key_just_pressed(Key key) {
        return first_frame_keys[key] && has_focus();
    }

    bool Input::is_key_just_released(Key key) {
        return released_keys[key] && has_focus();
    }

    bool Input::is_mouse_button_down(MouseButton button) {
        return mouse_buttons[button] && has_focus();
    }

    bool Input::is_mouse_button_just_pressed(MouseButton button) {
        return first_frame_mouse_buttons[button] && has_focus();
    }

    bool Input::is_mouse_button_just_released(MouseButton button) {
        return released_mouse_buttons[button] && has_focus();
    }

    bool Input::has_focus() {
        return glfwGetWindowAttrib(window->glfwWindow, GLFW_FOCUSED);
    }
}