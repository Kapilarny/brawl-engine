#include "shader.h"

#include "renderer_frontend.h"
#include "core/logger.h"
#include "gl/gl_shader.h"

shader* create_shader(const char *vertex_src, const char *fragment_src) {
    switch (get_renderer_api()) {
        case RENDERER_API::OPENGL: return {new gl_shader(vertex_src, fragment_src)};
        default: FATAL_ERROR("Unknown renderer!");
    }

    return nullptr;
}
