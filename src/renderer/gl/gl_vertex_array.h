#ifndef GL_VERTEX_ARRAY_H
#define GL_VERTEX_ARRAY_H

#include "renderer/vertex_array.h"

class gl_vertex_array : public vertex_array {
public:
    gl_vertex_array();
    ~gl_vertex_array() override;

    void bind() const override;
    void unbind() const override;

    void add_vertex_buffer(const vertex_buffer& vert_buffer) override;
    void set_index_buffer(const index_buffer& index_buffer) override;

    [[nodiscard]] const bvector<vertex_buffer*>& get_vertex_buffers() const override { return vertex_buffers; }
    [[nodiscard]] const index_buffer* get_index_buffer() const override { return index_buffer; }
private:
    u32 renderer_id{};
    u32 vertex_buffer_index = 0;
    bvector<vertex_buffer*> vertex_buffers;
    index_buffer* index_buffer;

    void init() override;
};

#endif //GL_VERTEX_ARRAY_H
