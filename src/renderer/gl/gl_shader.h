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

    void bind() const;
private:
    u32 program{};
};



#endif //GL_SHADER_H
