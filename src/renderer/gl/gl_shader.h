#ifndef GL_SHADER_H
#define GL_SHADER_H

#include "defines.h"

#include <glm/glm.hpp>

#include "renderer/shader.h"

class gl_shader : public shader {
public:
    gl_shader(const char* vertex_src, const char* fragment_src);
    ~gl_shader() override;

    void bind() const override;
    void unbind() const override;

    // Uniforms
    void set_i32(const char* name, i32 value) override;
    void set_u32(const char* name, u32 value) override;

    void set_f32(const char* name, f32 value) override;

    void set_bool(const char *name, bool value) override;

    void set_vec2(const char* name, const glm::vec2& value) override;
    void set_vec3(const char* name, const glm::vec3& value) override;
    void set_vec4(const char* name, const glm::vec4& value) override;

    void set_mat2(const char* name, const glm::mat2& value) override;
    void set_mat3(const char* name, const glm::mat3& value) override;
    void set_mat4(const char* name, const glm::mat4& value) override;

    void use() const;
private:
    u32 program{};
};



#endif //GL_SHADER_H
