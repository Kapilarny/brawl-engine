#ifndef GL_BUFFERS_H
#define GL_BUFFERS_H
#include "renderer/buffers.h"

class gl_vertex_buffer : public vertex_buffer {
public:
    explicit gl_vertex_buffer(u32 size);
    gl_vertex_buffer(const void* data, u32 size);

    ~gl_vertex_buffer() override;

    void bind() const override;
    void unbind() const override;

    void set_data(const void *data, u32 size) override;

    void set_layout(const buffer_layout& layout) override { this->layout = layout; }
    [[nodiscard]] const buffer_layout& get_layout() const override { return layout; }
private:
    u32 renderer_id{};
    buffer_layout layout;
};

class gl_index_buffer : public index_buffer {
public:
    gl_index_buffer(u32* indices, u32 count);
    ~gl_index_buffer() override;

    void bind() const override;
    void unbind() const override;

    [[nodiscard]] u32 get_count() const override { return count; }
private:
    u32 renderer_id{};
    u32 count{};
};

#endif //GL_BUFFERS_H
