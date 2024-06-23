#ifndef RENDERER_2D_H
#define RENDERER_2D_H

#include <glm/vec2.hpp>

#include "renderer_frontend.h"
#include "shader.h"
#include "texture.h"

class renderer_2d {
public:
    renderer_2d(window& window, RENDERER_API api);

    void begin();
    void end();

    void draw_quad(glm::vec2& position, glm::vec2& size, glm::vec4& color);
    void draw_quad(glm::vec2 position, glm::vec2 size, texture* texture);

    [[nodiscard]] const char* get_backend_name() const { return renderer->get_name(); }

    void set_clear_color(glm::vec4& color) const;
private:
    ptr_wrap<renderer_frontend> renderer;
    ptr_wrap<shader> quad_shader;

    ptr_wrap<vertex_array> quad_vertex_array;
    window& wnd;
};

#endif //RENDERER_2D_H
