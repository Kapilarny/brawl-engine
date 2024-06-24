#include "renderer_2d.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

renderer_2d::renderer_2d(window &window, RENDERER_API api) : renderer(create_renderer(api, window)), wnd(window) {
    quad_vertex_array = create_vertex_array();

    float verts[] = {
        // positions         // texture coords
         0.5f,  0.5f,  0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f,  0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f,  0.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f,  0.0f,   0.0f, 1.0f
    };

    vertex_buffer* vert_buff = vertex_buffer::create(verts, sizeof(verts));
    vert_buff->set_layout(buffer_layout({
        { shader_data_type::FLOAT3, "aPos" },
        { shader_data_type::FLOAT2, "aTexCoord" }
    }));

    u32 indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    index_buffer* index_buff = index_buffer::create(indices, sizeof(indices) / sizeof(u32));
    quad_vertex_array->add_vertex_buffer(vert_buff);
    quad_vertex_array->set_index_buffer(index_buff);

    quad_shader = create_shader("../shaders/test_shader.vert", "../shaders/test_shader.frag");
}

void renderer_2d::draw_quad(glm::vec2 &position, glm::vec2 &size, glm::vec4 &color) {

}

void renderer_2d::draw_quad(glm::vec2 position, glm::vec2 size, texture *tex) {
    auto model = glm::mat4(1.0f);
    auto view = glm::mat4(1.0f);
    auto projection = glm::mat4(1.0f);

    model = glm::translate(model, {position.x, position.y,0});
    model = glm::scale(model, {size.x, size.y, 0});
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    projection = glm::perspective(glm::radians(45.0f), (f32)wnd.get_width() / (f32)wnd.get_height(), 0.1f, 100.0f);

    tex->bind(0);

    quad_shader->bind();
    quad_shader->set_i32("texture1", 0);
    quad_shader->set_mat4("model", model);
    quad_shader->set_mat4("view", view);
    quad_shader->set_mat4("projection", projection);

    renderer->draw_indexed(quad_vertex_array, 6);
}

void renderer_2d::begin() {
    renderer->begin_render();
}

void renderer_2d::end() {
    renderer->end_render();
}

void renderer_2d::set_clear_color(glm::vec4 &color) const {
    renderer->set_clear_color(color);
}
