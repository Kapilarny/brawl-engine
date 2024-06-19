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

    // Add null-terminators to end of the files to ensure that the OpenGL compiles them properly
    vertex_bytes.push_back('\0');
    fragment_bytes.push_back('\0');

    u32 vert_id = glCreateShader(GL_VERTEX_SHADER);
    u32 frag_id = glCreateShader(GL_FRAGMENT_SHADER);

    // Vertex shader
    const char* vertex_source = (const char*)vertex_bytes.data();
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
    const char* fragment_source = (const char*)fragment_bytes.data();
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

void gl_shader::use() const {
    if(!program) {
        BERROR("Trying to use a shader which is not loaded!");
        return;
    }

    glUseProgram(program);
}

void gl_shader::set_i32(const char *name, i32 value) const {
    glUniform1i(glGetUniformLocation(program, name), value);
}

void gl_shader::set_u32(const char *name, u32 value) const {
    glUniform1ui(glGetUniformLocation(program, name), value);
}

void gl_shader::set_f32(const char *name, f32 value) const {
    glUniform1f(glGetUniformLocation(program, name), value);
}

void gl_shader::set_bool(const char *name, bool value) const {
    glUniform1f(glGetUniformLocation(program, name), value);
}