//
// Created by darby on 5/16/2024.
//
#pragma once

#include "window.h"
#include "input.h"
#include "memory.h"
#include "texture_utils.hpp"
#include "model.hpp"
#include "pipelines.hpp"
#include "camera.h"

namespace rockhopper {

void run_stencil_outline_scene(rockhopper::Window& window, rockhopper::Input& input);

void run_blend_scene(rockhopper::Window& window, rockhopper::Input& input);

}