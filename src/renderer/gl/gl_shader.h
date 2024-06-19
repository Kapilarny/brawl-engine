#ifndef GL_SHADER_H
#define GL_SHADER_H

#include "defines.h"

#include <glm/glm.hpp>

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

    void set_vec2(const char* name, const f32* value) const;
    void set_vec3(const char* name, const f32* value) const;
    void set_vec4(const char* name, const f32* value) const;

    void set_mat2(const char *name, const glm::mat2& value) const;
    void set_mat3(const char* name, const glm::mat3& value) const;
    void set_mat4(const char* name, const glm::mat4& value) const;


    void use() const;
private:
    u32 program{};
};



#endif //GL_SHADER_H
