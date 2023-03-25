//
// Created by darby on 3/24/2023.
//

#include "memory.h"
#include <stdlib.h>

namespace rockhopper {

    void StackAllocator::init( size_t size ) {
        memory = (u8*) malloc(size);
    }

}