#include "draw_system.h"

#include "ecs/components/texture_2d.h"

void draw_system::draw() {
    for(auto entity : entities) {
        auto& transform = entity.get_component<transform>();
        auto& texture = entity.get_component<texture_2d>();

        renderer.draw_tex_quad(transform.position.x, transform.position.y, texture.id);
    }
}
