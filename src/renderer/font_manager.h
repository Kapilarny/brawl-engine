//
// Created by user on 27.06.2024.
//

#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H

#include <glm/glm.hpp>

#include "defines.h"

class font_manager {
public:
    virtual ~font_manager() = default;

    static font_manager* create(const char* path);

    virtual void render_text(const char* text, glm::vec2 pos, f32 scale, glm::vec4 color) = 0;
};

#endif //FONT_MANAGER_H
