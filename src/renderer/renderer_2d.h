#ifndef RENDERER_2D_H
#define RENDERER_2D_H

#include <glm/vec2.hpp>

#include "renderer_frontend.h"
#include "shader.h"
#include "texture.h"
#include "core/camera.h"
#include "core/camera_2d.h"

class renderer_2d {
public:
    renderer_2d(window& wnd_ref, RENDERER_API api);

    void begin();
    void end();

    void set_blending(bool blend);

    void draw_quad(glm::vec2 position, glm::vec2 size, glm::vec4 color, f32 rotation = 0.0f);
    void draw_quad(glm::vec2 position, glm::vec2 size, texture* texture, f32 rotation = 0.0f);

    void render_text(const char* text, glm::vec2 pos, f32 scale, glm::vec4 color = {1.0f, 1.0f, 1.0f, 1.0f});

    [[nodiscard]] const char* get_backend_name() const { return renderer->get_name(); }
    [[nodiscard]] const camera_2d& get_camera() const { return cam; }
    [[nodiscard]] camera_2d& get_camera() { return cam; }
    [[nodiscard]] renderer_frontend* get_backend() const { return renderer.get(); }

    void set_clear_color(glm::vec4& color) const;
private:
    camera_2d cam;
    ptr_wrap<renderer_frontend> renderer;
    ptr_wrap<shader> tex_quad_shader;
    ptr_wrap<shader> color_quad_shader;

    ptr_wrap<vertex_array> tex_quad_vertex_array;
    ptr_wrap<vertex_array> color_quad_vertex_array;
    window& wnd;
};

#endif //RENDERER_2D_H
