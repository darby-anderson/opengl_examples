//
// Created by darby on 3/5/2023.
//

#pragma once

#include "window.h"
#include "platform.h"
#include "keys.h"

namespace rockhopper {

struct input {

public:

    void    init(Window* window);
    void    new_frame();

    bool    is_key_down(Key key);
    bool    is_key_just_pressed(Key key);
    bool    is_key_just_released(Key key);

    u8      keys[KEY_COUNT];
    u8      previous_keys[KEY_COUNT];


private:
    bool    has_focus();


        Window* window;

};

}

