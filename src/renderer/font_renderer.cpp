//
// Created by user on 27.06.2024.
//

#include "font_renderer.h"
#include "texture.h"

#include <ft2build.h>
#include <glm/ext/matrix_clip_space.hpp>

#include "core/camera.h"
#include "core/camera.h"
#include "core/camera.h"
#include "core/camera.h"
#include "core/camera.h"
#include "core/camera.h"
#include "core/camera.h"
#include "core/camera.h"

#include FT_FREETYPE_H

font_renderer::font_renderer(renderer_frontend* renderer, const char* font_path) : renderer(renderer) {
    FT_Library ft;
    ASSERT(!FT_Init_FreeType(&ft), "Failed to initialize FreeType");

    FT_Face face;
    ASSERT(!FT_New_Face(ft, font_path, 0, &face), "Failed to load font");

    FT_Set_Pixel_Sizes(face, 0, 48);

    for(u8 c = 0; c < 128; c++) {
        if(FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            BWARN("Failed to load glyph for character: %c", c);
            continue;
        }

        // Generate texture
        texture* tex = texture::create(face->glyph->bitmap.buffer, face->glyph->bitmap.width, face->glyph->bitmap.rows, texture_format::RED, {
                                           texture_filter::LINEAR,
                                           texture_filter::LINEAR,
                                           texture_edge_value_sampling::CLAMP_TO_EDGE,
                                           texture_edge_value_sampling::CLAMP_TO_EDGE,
                                           false
                                       });

        // Now store character for later use
        character chara = {
            tex,
            {face->glyph->bitmap.width, face->glyph->bitmap.rows},
            {face->glyph->bitmap_left, face->glyph->bitmap_top},
            (u32)face->glyph->advance.x
        };

        glyphs.insert(std::pair<char, character>(c, chara));
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    text_shader = create_shader("../shaders/font_shader.vert", "../shaders/font_shader.frag");

    vert_buff = vertex_buffer::create(6 * 4 * sizeof(f32));
    vert_buff->set_layout(buffer_layout({
        { shader_data_type::FLOAT4, "vertex" },
    }));

    vert_arr = create_vertex_array();
    vert_arr->add_vertex_buffer(vert_buff);
}

font_renderer::~font_renderer() {
    for(auto& [_, chara] : glyphs) {
        delete chara.tex;
    }
}

void font_renderer::render_text(const char *text, glm::vec2 pos, f32 scale, glm::vec3 color) {
    auto viewport = renderer->get_viewport(); // TODO: Add viewport resize callbacks to update this variable.
    auto projection = glm::ortho(0.0f, (f32)viewport.x, 0.0f, (f32)viewport.y); // TODO: This should be a member variable. It's redundant to calculate this every frame.

    text_shader->bind();
    text_shader->set_mat4("projection", projection);
    text_shader->set_vec3("textColor", color);

    vert_arr->bind();

    // Iterate through all characters
    for(const char* c = text; *c; c++) {
        character ch = glyphs[*c];

        f32 xpos = pos.x + ch.bearing.x * scale;
        f32 ypos = pos.y - (ch.size.y - ch.bearing.y) * scale;

        f32 w = ch.size.x * scale;
        f32 h = ch.size.y * scale;

        // Update VBO for each character
        f32 vertices[6][4] = {
            { xpos,     ypos + h,   0.0, 0.0 },
            { xpos,     ypos,       0.0, 1.0 },
            { xpos + w, ypos,       1.0, 1.0 },

            { xpos,     ypos + h,   0.0, 0.0 },
            { xpos + w, ypos,       1.0, 1.0 },
            { xpos + w, ypos + h,   1.0, 0.0 }
        };

        // Render glyph texture over quad
        ch.tex->bind(0);

        // Update content of VBO memory
        vert_buff->set_data(vertices, sizeof(vertices));

        // Render quad
        renderer->draw_arrays(vert_arr.get(), 6);

        // Now advance cursors for next glyph
        pos.x += (ch.advance >> 6) * scale; // Bitshift by 6 to get value in pixels (1/64th times 2^6 = 64)
    }
}
