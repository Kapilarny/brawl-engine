#ifndef BUFFERS_H
#define BUFFERS_H
#include "defines.h"
#include "core/logger.h"
#include "memory/bvector.h"

// This code is **highly** inspired by TheCherno's Hazel Engine

enum class shader_data_type {
    NONE = 0, FLOAT, FLOAT2, FLOAT3, FLOAT4, MAT3, MAT4, INT, INT2, INT3, INT4, BOOL
};

static u32 shader_data_type_size(shader_data_type type) {
    switch (type) {
        case shader_data_type::FLOAT: return 4;
        case shader_data_type::FLOAT2: return 4 * 2;
        case shader_data_type::FLOAT3: return 4 * 3;
        case shader_data_type::FLOAT4: return 4 * 4;
        case shader_data_type::MAT3: return 4 * 3 * 3;
        case shader_data_type::MAT4: return 4 * 4 * 4;
        case shader_data_type::INT: return 4;
        case shader_data_type::INT2: return 4 * 2;
        case shader_data_type::INT3: return 4 * 3;
        case shader_data_type::INT4: return 4 * 4;
        case shader_data_type::BOOL: return 1;

        default: FATAL_ERROR("Unknown shader data type!");
    }

    return 0;
}

struct buffer_element {
    const char* name;
    shader_data_type type;
    u32 size;
    u32 offset;
    bool normalized;

    buffer_element() = default;

    buffer_element(shader_data_type type, const char* name, bool normalized = false) : name(name), type(type), size(shader_data_type_size(type)), offset(0), normalized(normalized) {}

    [[nodiscard]] u32 get_component_count() const {
        switch (type) {
            case shader_data_type::FLOAT: return 1;
            case shader_data_type::FLOAT2: return 2;
            case shader_data_type::FLOAT3: return 3;
            case shader_data_type::FLOAT4: return 4;
            case shader_data_type::MAT3: return 3 * 3;
            case shader_data_type::MAT4: return 4 * 4;
            case shader_data_type::INT: return 1;
            case shader_data_type::INT2: return 2;
            case shader_data_type::INT3: return 3;
            case shader_data_type::INT4: return 4;
            case shader_data_type::BOOL: return 1;
            default: FATAL_ERROR("Unknown shader data type!");
        }

        return 0;
    }
};


class buffer_layout {
public:
    buffer_layout() = default;

    explicit buffer_layout(const bvector<buffer_element>& elements) : elements(elements) {
        u32 offset = 0;
        stride = 0;
        for (auto& element : elements) {
            element.offset = offset;
            offset += element.size;
            stride += element.size;
        }
    }

    [[nodiscard]] u32 get_stride() const { return stride; }
    [[nodiscard]] const bvector<buffer_element>& get_elements() const { return elements; }
private:
    bvector<buffer_element> elements;
    u32 stride = 0;
};

class vertex_buffer {
    virtual ~vertex_buffer() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual void set_data(const void* data, u32 size) = 0;

    [[nodiscard]] virtual const buffer_layout& get_layout() const = 0;
    virtual void set_layout(const buffer_layout& layout) = 0;

    static vertex_buffer* create(u32 size);
    static vertex_buffer* create(f32* vertices, u32 size);
};

class index_buffer {
    virtual ~index_buffer() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    [[nodiscard]] virtual u32 get_count() const = 0;

    static index_buffer* create(u32* indices, u32 count);
};

#endif //BUFFERS_H
