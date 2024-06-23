#ifndef SHADER_H
#define SHADER_H

#include <glm/fwd.hpp>

#include "defines.h"
#include "memory/ptr_wrap.h"

class shader {
public:
    virtual ~shader() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual void set_i32(const char* name, i32 value) = 0;
    virtual void set_u32(const char* name, u32 value) = 0;

    virtual void set_f32(const char* name, f32 value) = 0;

    virtual void set_bool(const char* name, bool value) = 0;

    virtual void set_vec2(const char* name, const glm::vec2& value) = 0;
    virtual void set_vec3(const char* name, const glm::vec3& value) = 0;
    virtual void set_vec4(const char* name, const glm::vec4& value) = 0;

    virtual void set_mat2(const char* name, const glm::mat2& value) = 0;
    virtual void set_mat3(const char* name, const glm::mat3& value) = 0;
    virtual void set_mat4(const char* name, const glm::mat4& value) = 0;
};

shader* create_shader(const char* vertex_src, const char* fragment_src);

#endif //SHADER_H
