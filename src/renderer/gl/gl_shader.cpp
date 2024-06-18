//
// Created by Matylda on 18.06.2024.
//

#include "gl_shader.h"

#include <glad/gl.h>

#include "core/logger.h"
#include "platform/platform.h"

bool gl_shader::create(const char *vertex_shader, const char *fragment_shader) {
    file_handle vertex_file{};
    if(!vertex_file.open(vertex_shader)) {
        BERROR("Failed to open vertex shader file: %s", vertex_shader);
        return false;
    }

    file_handle fragment_file{};
    if(!fragment_file.open(fragment_shader)) {
        BERROR("Failed to open fragment shader file: %s", fragment_shader);
        return false;
    }

    bvector<u8> vertex_bytes = vertex_file.read_bytes();
    bvector<u8> fragment_bytes = fragment_file.read_bytes();

    u32 vert_id = glCreateShader(GL_VERTEX_SHADER);
    u32 frag_id = glCreateShader(GL_FRAGMENT_SHADER);

    // Vertex shader
    const char* vertex_source = (const char*)vertex_bytes.begin();
    glShaderSource(vert_id, 1, &vertex_source, nullptr);
    glCompileShader(vert_id);

    u32 success;
    glGetShaderiv(vert_id, GL_COMPILE_STATUS, (int*)&success);
    if(!success) {
        char info_log[512];
        glGetShaderInfoLog(vert_id, 512, nullptr, info_log);
        BERROR("Failed to compile vertex shader: %s", info_log);
        return false;
    }

    // Fragment shader
    const char* fragment_source = (const char*)fragment_bytes.begin();
    glShaderSource(frag_id, 1, &fragment_source, nullptr);
    glCompileShader(frag_id);

    success = 0;
    glGetShaderiv(frag_id, GL_COMPILE_STATUS, (int*)&success);
    if(!success) {
        char info_log[512];
        glGetShaderInfoLog(frag_id, 512, nullptr, info_log);
        BERROR("Failed to compile fragment shader: %s", info_log);
        return false;
    }

    program = glCreateProgram();

    glAttachShader(program, vert_id);
    glAttachShader(program, frag_id);
    glLinkProgram(program);

    success = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int*)&success);
    if(!success) {
        char info_log[512];
        glGetProgramInfoLog(program, 512, nullptr, info_log);
        BERROR("Failed to link shader program: %s", info_log);
        return false;
    }

    glDeleteShader(vert_id);
    glDeleteShader(frag_id);

    return true;
}

gl_shader::~gl_shader() {
    if(program) glDeleteProgram(program);
}

void gl_shader::bind() const {
    if(!program) {
        BERROR("Trying to use an unbound shader!");
        return;
    }

    glUseProgram(program);
}
