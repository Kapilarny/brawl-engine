#ifndef GL_TEXTURE_H
#define GL_TEXTURE_H
#include "defines.h"

#include "renderer/texture.h"

class gl_texture : public texture {
public:
    gl_texture(const char* file_path, texture_format format, const texture_params& params);
    gl_texture(const void* data, i32 w, i32 h, texture_format format, const texture_params& params);
    ~gl_texture() override;

    void bind(u32 texture_id) override;
private:
    void load_texture(const void *data, texture_format format, const texture_params &params);

    u32 renderer_id{};
    i32 width{}, height{}, channels{};
};

#endif //GL_TEXTURE_H
