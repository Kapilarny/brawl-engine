#include "gl_texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stbi_image.h>

#include <glad/gl.h>

#include "core/logger.h"

gl_texture::~gl_texture() {
    if(texture) glDeleteTextures(1, &texture);
}

bool gl_texture::load_file(const char *file_path, texture_format format) {
    u8* data = stbi_load(file_path, &width, &height, &channels, 0);
    if(!data) {
        BERROR("Failed to load texture: %s", file_path);
        return false;
    }

    // Generate texture
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set wrapping/filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    u32 fmt = format == texture_format::RGB ? GL_RGB : GL_RGBA;

    glTexImage2D(GL_TEXTURE_2D, 0, fmt, width, height, 0, fmt, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Free image data
    stbi_image_free(data);

    return true;
}

void gl_texture::bind(u32 texture_id) const {
    if(!texture) {
        BERROR("Trying to bind a non-loaded texture!");
        return;
    }

    glActiveTexture(GL_TEXTURE0 + texture_id);
    glBindTexture(GL_TEXTURE_2D, texture);
}
