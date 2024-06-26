#ifndef GL_VERTEX_ARRAY_H
#define GL_VERTEX_ARRAY_H

#include "memory/ptr_wrap.h"
#include "renderer/vertex_array.h"

class gl_vertex_array : public vertex_array {
public:
    gl_vertex_array();
    ~gl_vertex_array() override;

    void bind() const override;
    void unbind() const override;

    void add_vertex_buffer(vertex_buffer* vert_buffer) override;
    void set_index_buffer(index_buffer* buffer) override;

    [[nodiscard]] const bvector<vertex_buffer*>& get_vertex_buffers() const override { return vertex_buffers; }
    [[nodiscard]] const index_buffer* get_index_buffer() const override { return idx_buffer.get(); }
private:
    u32 renderer_id{};
    u32 vertex_buffer_index = 0;
    bvector<vertex_buffer*> vertex_buffers;
    ptr_wrap<index_buffer> idx_buffer;
};

#endif //GL_VERTEX_ARRAY_H
