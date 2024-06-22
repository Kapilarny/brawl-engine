#include "gl_vertex_array.h"

#include <glad/gl.h>

gl_vertex_array::gl_vertex_array() {
    glGenVertexArrays(1, &renderer_id);
}

gl_vertex_array::~gl_vertex_array() {
    glDeleteVertexArrays(1, &renderer_id);
}

void gl_vertex_array::bind() const {
    glBindVertexArray(renderer_id);
}

void gl_vertex_array::unbind() const {
    glBindVertexArray(0);
}

GLenum shader_data_type_to_gl(shader_data_type type) {
    switch(type) {
        case shader_data_type::FLOAT:
        case shader_data_type::FLOAT2:
        case shader_data_type::FLOAT3:
        case shader_data_type::FLOAT4:
        case shader_data_type::MAT3:
        case shader_data_type::MAT4:
            return GL_FLOAT;

        case shader_data_type::INT:
        case shader_data_type::INT2:
        case shader_data_type::INT3:
        case shader_data_type::INT4:
            return GL_INT;

        case shader_data_type::BOOL: return GL_BOOL;

        default: ASSERT(false, "Unknown shader data type!");
    }
}

void gl_vertex_array::add_vertex_buffer(const vertex_buffer &vert_buffer) {
    ASSERT(vert_buffer.get_layout().get_elements().size(), "Vertex buffer has no layout!");

    glBindVertexArray(renderer_id);
    vert_buffer.bind();

    const auto& layout = vert_buffer.get_layout();
    for(int i = 0; i < layout.get_elements().size(); i++) {
        const auto& element = layout.get_elements()[i];

        glEnableVertexAttribArray(vertex_buffer_index);

        switch(element.type) {
            case shader_data_type::FLOAT:
            case shader_data_type::FLOAT2:
            case shader_data_type::FLOAT3:
            case shader_data_type::FLOAT4:
            case shader_data_type::MAT3:
            case shader_data_type::MAT4:
                glVertexAttribPointer(vertex_buffer_index, element.get_component_count(), shader_data_type_to_gl(element.type), element.normalized ? GL_TRUE : GL_FALSE, layout.get_stride(), (const void*)element.offset);
                break;

            case shader_data_type::INT:
            case shader_data_type::INT2:
            case shader_data_type::INT3:
            case shader_data_type::INT4:
            case shader_data_type::BOOL:
                glVertexAttribIPointer(vertex_buffer_index, element.get_component_count(), shader_data_type_to_gl(element.type), layout.get_stride(), (const void*)element.offset);
                break;

            default: ASSERT(false, "Unknown shader data type!");
        }
    }
}

void gl_vertex_array::set_index_buffer(index_buffer* buffer) {
    glBindVertexArray(renderer_id);
    buffer->bind();

    idx_buffer.reset(buffer);
}