//
// Created by darby on 3/5/2023.
//

#include <cstring>

#include "input.h"

namespace penguin {

    void input::init() {
        memset(keys, 0, KEY_COUNT);
        memset(previous_keys, 0, KEY_COUNT);
    }

    void input::new_frame() {
        for(u32 i = 0; i < KEY_COUNT; i++) {
            previous_keys[i] = keys[i];
        }
    }

    bool input::is_key_down(Key keys) {

    }

}