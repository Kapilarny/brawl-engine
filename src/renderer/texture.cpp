#include "texture.h"

#include "renderer_frontend.h"
#include "gl/gl_texture.h"

#include <stbi_image.h>

void texture::set_flip_y(bool flip) {
    stbi_set_flip_vertically_on_load(flip);
}

texture* create_texture(const char *file_path, texture_format format) {
    switch (get_renderer_api()) {
        case RENDERER_API::OPENGL: return new gl_texture(file_path, format);
        default: return nullptr;
    }
}
