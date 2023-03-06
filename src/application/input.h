//
// Created by darby on 3/5/2023.
//

#pragma once

#include "platform.h"
#include "keys.h"

namespace penguin {

struct input {

    void    init();

    bool    is_key_down(Key key);



    u8      keys[KEY_COUNT];
    u8      previous_keys[KEY_COUNT];


};

}

