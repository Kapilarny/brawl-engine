#include "buffers.h"

#include "renderer_frontend.h"
#include "gl/gl_buffers.h"

vertex_buffer* vertex_buffer::create(u32 size) {
    switch (get_renderer_api()) {
        case RENDERER_API::OPENGL: return new gl_vertex_buffer(size);
        default: FATAL_ERROR("Unknown renderer!");
    }

    return nullptr;
}

vertex_buffer* vertex_buffer::create(f32 *vertices, u32 size) {
    switch (get_renderer_api()) {
        case RENDERER_API::OPENGL: return new gl_vertex_buffer(vertices, size);
        default: FATAL_ERROR("Unknown renderer!");
    }

    return nullptr;
}

index_buffer* index_buffer::create(u32 *indices, u32 count) {
    switch (get_renderer_api()) {
        case RENDERER_API::OPENGL: return new gl_index_buffer(indices, count);
        default: FATAL_ERROR("Unknown renderer!");
    }

    return nullptr;
}
