#include "gl_texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stbi_image.h>

#include <glad/gl.h>
#include <glm/vec2.hpp>

#include "core/logger.h"

i32 texture_filter_to_gl(texture_filter wrap) {
    switch(wrap) {
        case texture_filter::LINEAR: return GL_LINEAR;
        case texture_filter::NEAREST: return GL_NEAREST;
        case texture_filter::NEAREST_MIPMAP_NEAREST: return GL_NEAREST_MIPMAP_NEAREST;
        case texture_filter::LINEAR_MIPMAP_NEAREST: return GL_LINEAR_MIPMAP_NEAREST;
        case texture_filter::NEAREST_MIPMAP_LINEAR: return GL_NEAREST_MIPMAP_LINEAR;
        case texture_filter::LINEAR_MIPMAP_LINEAR: return GL_LINEAR_MIPMAP_LINEAR;
        default: FATAL_ERROR("Unknown texture filter!"); return 0;
    }
}

i32 texture_edge_value_sampling_to_gl(texture_edge_value_sampling wrap) {
    switch(wrap) {
        case texture_edge_value_sampling::REPEAT: return GL_REPEAT;
        case texture_edge_value_sampling::MIRRORED_REPEAT: return GL_MIRRORED_REPEAT;
        case texture_edge_value_sampling::CLAMP_TO_EDGE: return GL_CLAMP_TO_EDGE;
        case texture_edge_value_sampling::CLAMP_TO_BORDER: return GL_CLAMP_TO_BORDER;
        // case texture_edge_value_sampling::MIRROR_CLAMP_TO_EDGE: return GL_MIRROR_CLAMP_TO_EDGE; // Requires OpenGL 4.4 or ARB_texture_mirror_clamp_to_edge
        default: FATAL_ERROR("Unknown texture edge value sampling!"); return 0;
    }
}

i32 texture_format_to_gl(texture_format format) {
    switch(format) {
        case texture_format::RGB: return GL_RGB;
        case texture_format::RGBA: return GL_RGBA;
        case texture_format::RED: return GL_RED;
        default: FATAL_ERROR("Unknown texture format!"); return 0;
    }
}

gl_texture::~gl_texture() {
    if(renderer_id) glDeleteTextures(1, &renderer_id);
}

gl_texture::gl_texture(const char *file_path, texture_format format, const texture_params &params) {
    u8* data = stbi_load(file_path, &width, &height, &channels, 0);
    if(!data) {
        BERROR("Failed to load texture: %s", file_path);
        return;
    }

    load_texture(data, format, params);

    // Free image data
    stbi_image_free(data);
}

gl_texture::gl_texture(const void *data, i32 w, i32 h, texture_format format, const texture_params &params) {
    width = w;
    height = h;

    load_texture(data, format, params);
}

void gl_texture::bind(u32 texture_id) {
    if(!renderer_id) {
        BERROR("Trying to bind a non-loaded texture!");
        return;
    }

    glActiveTexture(GL_TEXTURE0 + texture_id);
    glBindTexture(GL_TEXTURE_2D, renderer_id);
}

void gl_texture::load_texture(const void *data, texture_format format, const texture_params &params) {
    // Generate texture
    glGenTextures(1, &renderer_id);
    glBindTexture(GL_TEXTURE_2D, renderer_id);

    // Set wrapping/filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texture_edge_value_sampling_to_gl(params.wrap_s));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture_edge_value_sampling_to_gl(params.wrap_t));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texture_filter_to_gl(params.min_filter));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texture_filter_to_gl(params.mag_filter));

    const i32 fmt = texture_format_to_gl(format);

    glTexImage2D(GL_TEXTURE_2D, 0, fmt, width, height, 0, fmt, GL_UNSIGNED_BYTE, data);
    if(params.generate_mipmaps) glGenerateMipmap(GL_TEXTURE_2D);
}
