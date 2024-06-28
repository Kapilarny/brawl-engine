#include "texture.h"

#include "renderer_frontend.h"
#include "gl/gl_texture.h"

#include <stbi_image.h>

texture* texture::create(const char *file_path, texture_format format, const texture_params &params) {
    switch (get_renderer_api()) {
        case RENDERER_API::OPENGL: return new gl_texture(file_path, format, params);
        default: return nullptr;
    }
}

texture* texture::create(const void *data, texture_format format, const texture_params &params) {
    switch (get_renderer_api()) {
        case RENDERER_API::OPENGL: return new gl_texture(data, format, params);
        default: return nullptr;
    }
}

void texture::set_flip_y(bool flip) {
    stbi_set_flip_vertically_on_load(flip);
}