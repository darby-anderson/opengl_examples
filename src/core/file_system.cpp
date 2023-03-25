//
// Created by darby on 3/4/2023.
//
#include "file_system.h"

namespace rockhopper {

    static size_t file_get_size (FILE* file) {
        size_t fileSizeSigned;

        fseek(file, 0, SEEK_END);
        fileSizeSigned = ftell(file);
        fseek(file, 0, SEEK_SET);

        return fileSizeSigned;
    }

    FileReadResult file_read_text(cstring filename) {
        FileReadResult result {nullptr, 0};

        FILE* file = fopen(filename, "r");

        if(file) {
            size_t filesize = file_get_size(file);
            result.data = (char*)


        }


    }

}