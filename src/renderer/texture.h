#ifndef TEXTURE_H
#define TEXTURE_H
#include "defines.h"
#include "memory/ptr_wrap.h"

enum class texture_format {
    RGB,
    RGBA
};

class texture {
public:
    virtual ~texture() = default;

    virtual void bind(u32 texture_id) = 0;
};

texture* create_texture(const char* file_path, texture_format format);

#endif //TEXTURE_H
