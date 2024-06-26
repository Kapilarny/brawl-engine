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

class font_renderer {
public:
    font_renderer(renderer_frontend* renderer, const char* font_path);
    ~font_renderer();

    void render_text(const char *text, glm::vec2 pos, float scale, glm::vec3 color);
private:
    renderer_frontend* renderer;
    ptr_wrap<shader> text_shader;
    ptr_wrap<vertex_array> vert_arr;
    vertex_buffer* vert_buff; // This CANNOT be a ptr_wrap because it gets deleted in the destructor of vertex_array
    std::map<char, character> glyphs;
};

#endif //FONT_MANAGER_H
