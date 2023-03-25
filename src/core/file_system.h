//
// Created by darby on 3/4/2023.
//

#pragma once

#include "platform.h"

#include <cstdio>

namespace rockhopper {

    struct FileReadResult {
        char*               data;
        size_t              size;
    };


    FileReadResult          file_read_text(cstring filename);

}