#ifndef TEXTURE_H
#define TEXTURE_H
#include "defines.h"
#include "memory/ptr_wrap.h"

enum class texture_format {
    RGB,
    RGBA,
    RED
};


// https://www.khronos.org/opengl/wiki/Sampler_Object#Sampling_parameters
enum class texture_filter {
    LINEAR,
    NEAREST,
    NEAREST_MIPMAP_NEAREST,
    LINEAR_MIPMAP_NEAREST,
    NEAREST_MIPMAP_LINEAR,
    LINEAR_MIPMAP_LINEAR
};

enum class texture_edge_value_sampling {
    REPEAT,
    MIRRORED_REPEAT,
    CLAMP_TO_EDGE,
    CLAMP_TO_BORDER,
    // MIRROR_CLAMP_TO_EDGE (requires OpenGL 4.4 or ARB_texture_mirror_clamp_to_edge)
};

// default values are yoinked from https://learnopengl.com/Getting-started/Textures
// btw wtf copilot knew immediately the website :kekw:
// bros an expert at yoinking stuff ig
struct texture_params {
    texture_filter min_filter = texture_filter::LINEAR_MIPMAP_LINEAR;
    texture_filter mag_filter = texture_filter::LINEAR;
    texture_edge_value_sampling wrap_s = texture_edge_value_sampling::REPEAT;
    texture_edge_value_sampling wrap_t = texture_edge_value_sampling::REPEAT;
    bool generate_mipmaps = true;
};

class texture {
public:
    virtual ~texture() = default;
    static texture* create(const char* file_path, texture_format format, const texture_params& params = {});
    static texture* create(const void *data, i32 w, i32 h, texture_format format, const texture_params &params = {});

    virtual void bind(u32 texture_id) = 0;
    static void set_flip_y(bool flip);

    [[nodiscard]] i32 get_width() const { return width; }
    [[nodiscard]] i32 get_height() const { return height; }
protected:
    i32 width{}, height{};
};

#endif //TEXTURE_H
