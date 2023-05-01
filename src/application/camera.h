//
// Created by darby on 4/6/2023.
//

#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <unordered_map>

#include "keys.h"
#include "input.h"

namespace rockhopper {

    /*enum Camera_Movement {
        CAMERA_MOVEMENT_FORWARD,
        CAMERA_MOVEMENT_BACKWARD,
        CAMERA_MOVEMENT_LEFT,
        CAMERA_MOVEMENT_RIGHT,
        CAMERA_MOVEMENT_NONE
    };*/



struct camera {

public:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    float yaw;
    float pitch;
    float movement_speed;
    float mouse_sensitivity;
    float zoom;

    void init(glm::vec3 cameraPos, glm::vec3 cameraUp) {
        yaw = YAW;
        pitch = PITCH;
        movement_speed = SPEED;
        mouse_sensitivity = SENSITIVITY;
        zoom = ZOOM;

        this->position = cameraPos;
        this->worldUp = cameraUp;
        this->up = cameraUp;
        front = glm::vec3(0.0f, 0.0f, -1.0f);

        std::cout << "camera position: (" << position.x  << "," << position.y  << "," << position.z << ")" << std::endl;
        std::cout << "camera front: (" << front.x  << "," << front.y  << "," << front.z << ")" << std::endl;
        std::cout << "camera up: (" << up.x  << "," << up.y  << "," << up.z << ")" << std::endl;
        std::cout << "cameraUp: (" << cameraUp.x  << "," << cameraUp.y  << "," << cameraUp.z << ")" << std::endl;


        update_camera_vectors();

        std::cout << "camera position: (" << position.x  << "," << position.y  << "," << position.z << ")" << std::endl;
        std::cout << "camera front: (" << front.x  << "," << front.y  << "," << front.z << ")" << std::endl;
        std::cout << "camera up: (" << up.x  << "," << up.y  << "," << up.z << ")" << std::endl;
        std::cout << "cameraUp: (" << cameraUp.x  << "," << cameraUp.y  << "," << cameraUp.z << ")" << std::endl;

    }

    glm::mat4 get_view_matrix() const {
        return glm::lookAt(position, position + front, up);
    }

    void processInput(input* in, float deltaTime) {

        // return;

        // KEYBOARD INPUT
        float velocity = movement_speed * deltaTime;
        if(in->is_key_down(KEY_W)) {
            position += front * velocity;
        }
        if(in->is_key_down(KEY_S)) {
            position -= front * velocity;
        }
        if(in->is_key_down(KEY_A)) {
            position -= right * velocity;
        }
        if(in->is_key_down(KEY_D)) {
            position += right * velocity;
        }

        // MOUSE MOVE INPUT
        MouseMoveData mouse_move_data = in->get_mouse_move_info_this_frame();
        if(mouse_move_data.has_moved) {
            float xOffset = mouse_move_data.previous_x_position - mouse_move_data.x_position;
            float yOffset = mouse_move_data.previous_y_position - mouse_move_data.y_position;

            xOffset *= mouse_sensitivity;
            yOffset *= mouse_sensitivity;

            yaw += xOffset;
            pitch += yOffset;

            if(pitch > 89.0f) {
                pitch = 89.0f;
            } else if(pitch < -89.0f) {
                pitch = -89.0f;
            }

            update_camera_vectors();
        }

        // SCROLL INPUT
        ScrollData scroll_data = in->get_scroll_info_this_frame();
        if(scroll_data.has_scrolled) {
            zoom -= (float) scroll_data.y_offset;
            if(zoom < 1.0f) {
                zoom = 1.0f;
            }
            if(zoom > 45.0f) {
                zoom = 45.0f;
            }

            std::cout << "scrolling. zoom: " << zoom << std::endl;
        }

    }

private:
    const float YAW = -90.0f;
    const float PITCH = 0.0f;
    const float SPEED = 2.5f;
    const float SENSITIVITY = 0.1f;
    const float ZOOM = 45.0f;

    void update_camera_vectors() {
        // calculate the new front vector
        glm::vec3 unnormalized_front;
        unnormalized_front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        unnormalized_front.y = sin(glm::radians(pitch));
        unnormalized_front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(unnormalized_front);

        // std::cout << "Updating camera vectors" << std::endl;
        // std::cout << "camera front: (" << front.x  << "," << front.y  << "," << front.z << ")" << std::endl;
        // std::cout << "worldUp: (" << worldUp.x  << "," << worldUp.y  << "," << worldUp.z << ")" << std::endl;
        // std::cout << "right: (" << right.x  << "," << right.y  << "," << right.z << ")" << std::endl;

        // also re-calculate the right and up vector
        right = glm::normalize(glm::cross(front, worldUp));

        glm::vec3 unnormal_up = glm::cross(right, front);
        // std::cout << "unnormal_up: (" << unnormal_up.x  << "," << unnormal_up.y  << "," << unnormal_up.z << ")" << std::endl;
        up = glm::normalize(unnormal_up);
        // std::cout << "up: (" << up.x  << "," << up.y  << "," << up.z << ")" << std::endl;

    }
};

};