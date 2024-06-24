#include "gl_buffers.h"

#include <glad/gl.h>

gl_vertex_buffer::gl_vertex_buffer(u32 size) {
    glGenBuffers(1, &renderer_id);
    glBindBuffer(GL_ARRAY_BUFFER, renderer_id);
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

gl_vertex_buffer::gl_vertex_buffer(const void *data, u32 size) {
    glGenBuffers(1, &renderer_id);
    glBindBuffer(GL_ARRAY_BUFFER, renderer_id);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

gl_vertex_buffer::~gl_vertex_buffer() {
    glDeleteBuffers(1, &renderer_id);
}

void gl_vertex_buffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, renderer_id);
}

void gl_vertex_buffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void gl_vertex_buffer::set_data(const void *data, u32 size) {
    glBindBuffer(GL_ARRAY_BUFFER, renderer_id);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

gl_index_buffer::gl_index_buffer(u32 *indices, u32 count) : count(count) {
    glGenBuffers(1, &renderer_id);

    // GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
    // Binding with GL_ARRAY_BUFFER allows the data to be loaded regardless of VAO state.
    glBindBuffer(GL_ARRAY_BUFFER, renderer_id);
    glBufferData(GL_ARRAY_BUFFER, count * sizeof(u32), indices, GL_STATIC_DRAW);
}

gl_index_buffer::~gl_index_buffer() {
    glDeleteBuffers(1, &renderer_id);
}

void gl_index_buffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id);
}

void gl_index_buffer::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}