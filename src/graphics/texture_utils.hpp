//
// Created by darby on 5/19/2024.
//

#pragma once

#include "platform.h"
#include "texture_utils.hpp"
#include <string>
#include <iostream>

#ifndef GLAD_AND_GLFW
#define GLAD_AND_GLFW
#include <glad/glad.h>
#endif

#include "stb_image.h"

namespace rockhopper::utils {

uint32_t texture_from_file(cstring path, const std::string& directory, bool gamma);

}
