#include "vertex_array.h"

#include "renderer_frontend.h"
#include "gl/gl_vertex_array.h"

ptr_wrap<vertex_array> create_vertex_array() {
    switch (get_renderer_api()) {
        case RENDERER_API::OPENGL: return new gl_vertex_array();
        default: FATAL_ERROR("Unknown renderer!");
    }

    return nullptr;
}
