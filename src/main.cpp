#include <iostream>

#include "core/logger.h"
#include "platform/platform.h"
#include "renderer/renderer_2d.h"
#include "renderer/renderer_frontend.h"

int main() {
    window w("Brawl Engine", 800, 600);
    auto rend = renderer_2d(w, RENDERER_API::OPENGL);

    BINFO("Created renderer: %s", rend.get_backend_name());

    // Make the clear color red
    glm::vec4 color = {1.0f, 0.0f, 0.0f, 1.0f};
    rend.set_clear_color(color);

    glm::vec2 pos = {0, 0};
    i32 multiplier = 1;
    texture* tex = create_texture("../resources/awesomeface.png", texture_format::RGBA);
    while(!w.should_close()) {
        w.poll_events();

        if(pos.x >= 1.5 || pos.x <= -1.5) {
            multiplier *= -1;
        }

        pos.x += 0.001 * multiplier;

        rend.begin();

        rend.draw_quad(pos, {1, 1}, tex);

        rend.end();
    }

    return 0;
}