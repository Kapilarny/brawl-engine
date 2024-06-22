#ifndef GL_TEXTURE_H
#define GL_TEXTURE_H
#include "defines.h"

#include "renderer/texture.h"

class gl_texture : public texture {
public:
    gl_texture(const char* file_path, texture_format format);
    ~gl_texture() override;

    void bind(u32 texture_id) override;
private:
    u32 renderer_id{};
    i32 width{}, height{}, channels{};
};

#endif //GL_TEXTURE_H
