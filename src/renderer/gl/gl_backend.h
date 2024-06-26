#ifndef GL_BACKEND_H
#define GL_BACKEND_H

#include "gl_shader.h"
#include "gl_texture.h"
#include "renderer/renderer_frontend.h"

class gl_backend : public renderer_frontend {
public:
    explicit gl_backend(window& window);
    ~gl_backend() override;

    void begin_render() override;
    void end_render() override;

    void set_blending(bool blend) override;
    void set_clear_color(glm::vec4& color) override { clear_color = color; }
    void set_viewport(u32 x, u32 y, u32 width, u32 height) override;
    glm::vec2 get_viewport() override { return {wnd.get_width(), wnd.get_height()}; }

    void draw_indexed(vertex_array* vertex_array, u32 index_count) override;
    void draw_arrays(vertex_array* vertex_array, u32 count) override;

    const char* get_name() override;
private:
    bool drawing = false;
    u32 vbo{}, vao{}, ebo{};
    glm::vec4 clear_color{};
    // gl_shader shader;
    // gl_texture container, face{};
};

#endif //GL_BACKEND_H
