//
// Created by user on 27.06.2024.
//

#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H

#include <map>
#include <glm/glm.hpp>

#include "defines.h"
#include "renderer_frontend.h"
#include "shader.h"
#include "texture.h"

struct character {
    texture* tex;
    glm::ivec2 size;
    glm::ivec2 bearing;
    u32 advance;
};

class font_manager {
public:
    font_manager(renderer_frontend& renderer, const char* font_path);
    ~font_manager();

    void render_text(const char* text, glm::vec2 pos, f32 scale, glm::vec4 color);
private:
    renderer_frontend& renderer;
    ptr_wrap<shader> text_shader;
    ptr_wrap<vertex_buffer> vert_buff;
    std::map<char, character> glyphs;
};

#endif //FONT_MANAGER_H
