#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H
#include "buffers.h"

class vertex_array {
public:
    vertex_array() = default;
    virtual ~vertex_array() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual void add_vertex_buffer(const vertex_buffer& vert_buffer) = 0;
    virtual void set_index_buffer(index_buffer* index_buffer) = 0;

    [[nodiscard]] virtual const bvector<vertex_buffer*>& get_vertex_buffers() const = 0;
    [[nodiscard]] virtual const index_buffer* get_index_buffer() const = 0;

    static vertex_array* create();
};

#endif //VERTEX_ARRAY_H
