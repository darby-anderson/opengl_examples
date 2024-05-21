#include "pipelines.hpp"

namespace rockhopper::pipelines {

// BASIC MVP PIPELINE - USING MODEL
/*
 * vert shader:
 * attributes:
 * aPos
 * aNormal
 * aTexCoords
 *
 * uniforms:
 * vec4 model
 * vec4 view
 * vec4 projection
 *
 * frag shader:
 * uniforms:
 * sampler2D texture_diffuse1;
 *
 * */

void init_basic_mvp_model(shader sh, glm::mat4 view, glm::mat4 projection) {
    sh.setFloatMatrix4("projection", projection);
    sh.setFloatMatrix4("view", view);
}

void draw_basic_mvp_model(shader sh, model geometric_model, glm::vec3 translation, glm::vec3 scale) {
    glm::mat4 model_mat = glm::mat4(1.0f);
    model_mat = glm::translate(model_mat, translation);
    model_mat = glm::scale(model_mat, scale);
    sh.setFloatMatrix4("model", model_mat);

    sh.setFloatMatrix4("model", model_mat);

    geometric_model.draw(sh);
}

// BASIC MVP PIPELINE - NO MODEL - INSTANCING SUPPORT
/*
 * vert shader:
 * attributes:
 * aPos
 * aTexCoords
 *
 * uniforms:
 * vec4 model
 * vec4 view
 * vec4 projection
 *
 * frag shader:
 * uniforms:
 * sampler2D texture1;
 *
 * */
void init_basic_raw_data(shader sh, glm::mat4 view, glm::mat4 projection) {
    sh.setFloatMatrix4("projection", projection);
    sh.setFloatMatrix4("view", view);
}

// useful when drawing multiple instances of a single object
void set_instancing_data_basic_raw_data(uint32_t mesh_vao, uint32_t texture_id) {
    glBindVertexArray(mesh_vao);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id);
}
void draw_basic_raw_data(shader sh, uint32_t triangle_count, glm::vec3 translation, glm::vec3 scale) {
    glm::mat4 model_mat = glm::mat4(1.0f);
    model_mat = glm::translate(model_mat, translation);
    model_mat = glm::scale(model_mat, scale);

    sh.setFloatMatrix4("model", model_mat);
    glDrawArrays(GL_TRIANGLES, 0, triangle_count);
}

}