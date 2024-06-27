//
// Created by user on 27.06.2024.
//

#ifndef GL_FONT_MANAGER_H
#define GL_FONT_MANAGER_H

#include <map> // TODO: implement a hashmap

#include "renderer/font_manager.h"
#include "renderer/shader.h"

struct character {
    u32 texture_id;
    glm::ivec2 size;
    glm::ivec2 bearing;
    u32 advance;
};

class gl_font_manager : public font_manager {
public:
    gl_font_manager(const char* path);
    ~gl_font_manager() override;

    void render_text(const char* text, glm::vec2 pos, f32 scale, glm::vec4 color) override;
private:
    ptr_wrap<shader> text_shader;

    u32 VAO, VBO;
    std::map<char, character> glyphs;
};

#endif //GL_FONT_MANAGER_H
