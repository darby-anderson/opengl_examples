#pragma once

#include <glm/glm.hpp>

#include "shader.h"
#include "model.hpp"

namespace rockhopper::pipelines {

// Associated with shaders/model_loading
void init_basic_mvp_model(shader sh, glm::mat4 view, glm::mat4 projection);
void draw_basic_mvp_model(shader sh, model geometric_model, glm::vec3 translation, glm::vec3 scale);

void init_basic_raw_data(shader sh, glm::mat4 view, glm::mat4 projection);
void set_instancing_data_basic_raw_data(uint32_t mesh_vao, uint32_t texture_id);
void draw_basic_raw_data(shader sh, uint32_t triangle_count, glm::vec3 translation, glm::vec3 scale);

}
