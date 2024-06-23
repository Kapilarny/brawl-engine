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

    while(!w.should_close()) {
        w.poll_events();

        rend.begin();

        rend.draw_quad({10.f, 10.f}, {1, 1}, nullptr);\

        rend.end();
    }

    return 0;
}