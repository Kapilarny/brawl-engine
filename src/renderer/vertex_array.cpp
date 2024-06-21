#include "vertex_array.h"

#include "renderer_frontend.h"
#include "gl/gl_vertex_array.h"

vertex_array* vertex_array::create() {
    switch (get_renderer_api()) {
        case RENDERER_API::OPENGL: return new gl_vertex_array();
        default: FATAL_ERROR("Unknown renderer!");
    }

    return nullptr;
}
