#ifndef RENDERER_2D_H
#define RENDERER_2D_H

#include <glm/vec2.hpp>

#include "renderer_frontend.h"
#include "shader.h"
#include "texture.h"
#include "core/camera.h"

class renderer_2d {
public:
    renderer_2d(window& wnd_ref, RENDERER_API api);

    void begin();
    void end();

    void set_blending(bool blend);

    void draw_quad(glm::vec2& position, glm::vec2& size, glm::vec4& color);
    void draw_quad(glm::vec2 position, glm::vec2 size, texture* texture);

    [[nodiscard]] const char* get_backend_name() const { return renderer->get_name(); }
    [[nodiscard]] const camera& get_camera() const { return cam; }
    [[nodiscard]] camera& get_camera() { return cam; }

    void set_clear_color(glm::vec4& color) const;
private:
    camera cam;
    ptr_wrap<renderer_frontend> renderer;
    shader* quad_shader;

    vertex_array* quad_vertex_array;
    window& wnd;
};

#endif //RENDERER_2D_H
