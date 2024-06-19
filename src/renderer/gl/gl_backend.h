//
// Created by Matylda on 18.06.2024.
//

#ifndef GL_BACKEND_H
#define GL_BACKEND_H

#include "gl_shader.h"
#include "renderer/renderer_frontend.h"

class gl_backend : public renderer_frontend {
public:
    explicit gl_backend(window& window);
    ~gl_backend() override;

    void render() override;
    const char* get_name() override;
private:
    u32 vbo, vao, ebo;
    gl_shader shader;
};

#endif //GL_BACKEND_H
