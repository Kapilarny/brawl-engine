#ifndef GL_TEXTURE_H
#define GL_TEXTURE_H
#include "defines.h"

enum class texture_format {
    RGB,
    RGBA
};

class gl_texture {
public:
    gl_texture() = default;
    ~gl_texture();

    bool load_file(const char* file_path, texture_format format);
    void bind(u32 texture_id) const;
private:
    u32 texture;
    i32 width, height, channels;
};

#endif //GL_TEXTURE_H
