#include "renderer_2d.h"


void renderer_2d::begin() {
    renderer->begin_render();
}

void renderer_2d::end() {
    renderer->end_render();
}

void renderer_2d::set_clear_color(glm::vec4 &color) const {
    renderer->set_clear_color(color);
}
