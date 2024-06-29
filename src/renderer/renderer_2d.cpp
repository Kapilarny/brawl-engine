#include "renderer_2d.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

renderer_2d::renderer_2d(window &wnd_ref, RENDERER_API api) : renderer(create_renderer(api, wnd_ref)), wnd(wnd_ref) {
    cam = camera_2d(renderer.get());

    // tex_quad_vertex_array
    {
        tex_quad_vertex_array = create_vertex_array();

        float verts[] = {
            // positions          // texture coords
            0.5f,  0.5f,  1.0f, 1.0f,   // top right
            0.5f, -0.5f,  1.0f, 0.0f,   // bottom right
           -0.5f, -0.5f,  0.0f, 0.0f,   // bottom left
           -0.5f,  0.5f,  0.0f, 1.0f
       };

        vertex_buffer* vert_buff = vertex_buffer::create(verts, sizeof(verts));
        vert_buff->set_layout(buffer_layout({
            { shader_data_type::FLOAT2, "aPos" },
            { shader_data_type::FLOAT2, "aTexCoord" }
        }));

        u32 indices[] = {
            0, 1, 3,
            1, 2, 3
        };

        index_buffer* index_buff = index_buffer::create(indices, sizeof(indices) / sizeof(u32));
        tex_quad_vertex_array->add_vertex_buffer(vert_buff);
        tex_quad_vertex_array->set_index_buffer(index_buff);

        tex_quad_shader = create_shader("../shaders/tex_quad_shader.vert", "../shaders/tex_quad_shader.frag");
    }

    {
        color_quad_vertex_array = create_vertex_array();

        float verts[] = {
            // positions
            0.5f,  0.5f,
            0.5f, -0.5f,
           -0.5f, -0.5f,
           -0.5f,  0.5f,
       };

        vertex_buffer* vert_buff = vertex_buffer::create(verts, sizeof(verts));
        vert_buff->set_layout(buffer_layout({
            { shader_data_type::FLOAT2, "aPos" }
        }));

        u32 indices[] = {
            0, 1, 3,
            1, 2, 3
        };

        index_buffer* index_buff = index_buffer::create(indices, sizeof(indices) / sizeof(u32));
        color_quad_vertex_array->add_vertex_buffer(vert_buff);
        color_quad_vertex_array->set_index_buffer(index_buff);

        color_quad_shader = create_shader("../shaders/col_quad_shader.vert", "../shaders/col_quad_shader.frag");
    }
}

void renderer_2d::draw_quad(glm::vec2 position, glm::vec2 size, glm::vec4 color, f32 rotation) {
    auto model = glm::mat4(1.0f);
    // auto view = cam.get_view();
    auto projection = cam.get_projection();

    model = glm::translate(model, {position.x, position.y,0});
    model = glm::scale(model, {size.x, size.y, 0});
    model = glm::rotate(model, rotation, {0, 0, 1});

    color_quad_shader->bind();
    color_quad_shader->set_vec4("color", color);
    color_quad_shader->set_mat4("model", model);
    // color_quad_shader->set_mat4("view", view);
    color_quad_shader->set_mat4("projection", projection);

    renderer->draw_indexed(color_quad_vertex_array.get(), 6);
}

void renderer_2d::draw_quad(glm::vec2 position, glm::vec2 size, texture *tex, f32 rotation) {
    auto model = glm::mat4(1.0f);
    // auto view = cam.get_view();
    auto projection = cam.get_projection();

    model = glm::translate(model, {position.x + size.x / 2, position.y + size.y / 2,0});
    model = glm::scale(model, {size.x, size.y, 0});
    model = glm::rotate(model, rotation, {0, 0, 1});

    tex->bind(0);

    tex_quad_shader->bind();
    tex_quad_shader->set_i32("texture1", 0);
    tex_quad_shader->set_mat4("model", model);
    // tex_quad_shader->set_mat4("view", view);
    tex_quad_shader->set_mat4("projection", projection);

    renderer->draw_indexed(tex_quad_vertex_array.get(), 6);
}

void renderer_2d::render_text(const char *text, glm::vec2 pos, f32 scale, glm::vec4 color) {\

}

void renderer_2d::begin() {
    renderer->begin_render();
}

void renderer_2d::end() {
    renderer->end_render();
}

void renderer_2d::set_blending(bool blend) {
    renderer->set_blending(blend);
}

void renderer_2d::set_clear_color(glm::vec4 &color) const {
    renderer->set_clear_color(color);
}
