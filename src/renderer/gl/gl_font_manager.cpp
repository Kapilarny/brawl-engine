//
// Created by user on 27.06.2024.
//

// #include "gl_font_manager.h"

#include <glad/gl.h>

#include "gl_vertex_array.h"
#include "core/logger.h"
#include "renderer/texture.h"
#include "renderer/vertex_array.h"

#include <ft2build.h>
#include FT_FREETYPE_H

// gl_font_manager::gl_font_manager(const char *path) {
//
// }
//
// gl_font_manager::~gl_font_manager() {
//     // Delete all textures
//     for(auto& [_, chara] : glyphs) {
//         delete chara.texture;
//     }
// }
//
// void gl_font_manager::render_text(const char *text, glm::vec2 pos, f32 scale, glm::vec4 color) {
//     text_shader->bind();
//     text_shader->set_vec4("textColor", color);
//
//     vert_buff->bind();
//
//     // Iterate through all characters
//     for(const char* c = text; *c; c++) {
//         character ch = glyphs[*c];
//
//         f32 xpos = pos.x + ch.bearing.x * scale;
//         f32 ypos = pos.y - (ch.size.y - ch.bearing.y) * scale;
//
//         f32 w = ch.size.x * scale;
//         f32 h = ch.size.y * scale;
//
//         // Update VBO for each character
//         f32 vertices[6][4] = {
//             { xpos,     ypos + h,   0.0, 0.0 },
//             { xpos,     ypos,       0.0, 1.0 },
//             { xpos + w, ypos,       1.0, 1.0 },
//
//             { xpos,     ypos + h,   0.0, 0.0 },
//             { xpos + w, ypos,       1.0, 1.0 },
//             { xpos + w, ypos + h,   1.0, 0.0 }
//         };
//
//         // Render glyph texture over quad
//         ch.texture->bind(0);
//
//         // Update content of VBO memory
//         vert_buff->set_data(vertices, sizeof(vertices));
//
//         // Render quad
//         glDrawArrays(GL_TRIANGLES, 0, 6);
//
//         // Now advance cursors for next glyph
//         pos.x += (ch.advance >> 6) * scale; // Bitshift by 6 to get value in pixels (1/64th times 2^6 = 64)
//     }
// }
