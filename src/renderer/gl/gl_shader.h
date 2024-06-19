//
// Created by Matylda on 18.06.2024.
//

#ifndef GL_SHADER_H
#define GL_SHADER_H
#include "defines.h"


class gl_shader {
public:
    gl_shader() = default;
    ~gl_shader();

    bool create(const char* vertex_shader, const char* fragment_shader);

    // Uniforms
    void set_i32(const char* name, i32 value) const;
    void set_u32(const char* name, u32 value) const;

    void set_f32(const char* name, f32 value) const;

    void set_bool(const char* name, bool value) const;

    void use() const;
private:
    u32 program{};
};



#endif //GL_SHADER_H
