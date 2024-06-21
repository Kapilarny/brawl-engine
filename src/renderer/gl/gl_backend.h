#ifndef GL_BACKEND_H
#define GL_BACKEND_H

#include "gl_shader.h"
#include "gl_texture.h"
#include "renderer/renderer_frontend.h"

class gl_backend : public renderer_frontend {
public:
    explicit gl_backend(window& window);
    ~gl_backend() override;

    void render() override;

    void draw_indexed(u32 vao, u32 ebo, u32 index_count) override;
    void set_clear_color(glm::vec4& color) override { clear_color = color; }
    void set_viewport(u32 x, u32 y, u32 width, u32 height) override;

    const char* get_name() override;
private:
    bool drawing = false;
    u32 vbo{}, vao{}, ebo{};
    glm::vec4 clear_color{};
    gl_shader shader;
    gl_texture container{}, face{};
};

#endif //GL_BACKEND_H
