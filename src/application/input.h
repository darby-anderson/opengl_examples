//
// Created by darby on 3/5/2023.
//

#pragma once

#include "window.h"
#include "platform.h"
#include "keys.h"
#include "mouse_button.h"

namespace rockhopper {

    struct ScrollData {
        bool has_scrolled = false;
        f32 x_offset = 0;
        f32 y_offset = 0;
    };

    struct MouseMoveData {
        bool has_moved = false;
        f32 previous_x_position = 0;
        f32 previous_y_position = 0;
        f32 x_position = 0;
        f32 y_position = 0;
    };

    struct InputConfiguration {
        Window* window = nullptr;
    };

struct input {

public:

    void    init(InputConfiguration* input_configuration);
    void    start_new_frame();

    bool    is_key_down(Key key);
    bool    is_key_just_pressed(Key key);
    bool    is_key_just_released(Key key);

    bool    is_mouse_button_down(MouseButton button);
    bool    is_mouse_button_just_pressed(MouseButton button);
    bool    is_mouse_button_just_released(MouseButton button);

    u8      keys[KEY_COUNT];
    u8      first_frame_keys[KEY_COUNT];
    u8      released_keys[KEY_COUNT];

    u8      mouse_buttons[MOUSE_BUTTON_COUNT];
    u8      first_frame_mouse_buttons[MOUSE_BUTTON_COUNT];
    u8      released_mouse_buttons[MOUSE_BUTTON_COUNT];

    void    on_mouse_move(f32 new_position_x, f32 new_position_y);
    void    on_scroll(f32 x_pos, f32 y_pos);

    ScrollData  get_scroll_info_this_frame();
    MouseMoveData get_mouse_move_info_this_frame();

private:
    bool    has_focus();

    Window* window;

    MouseMoveData mouse_move_data;
    ScrollData  scroll_data;

    bool    has_ever_received_mouse_data = false;
    bool    has_ever_received_scroll_data = false;

};

}

