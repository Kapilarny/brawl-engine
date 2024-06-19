#include <iostream>

#include "core/logger.h"
#include "platform/platform.h"
#include "renderer/renderer_frontend.h"

int main() {
    window w("Brawl Engine", 800, 600);
    renderer_frontend* rend = create_renderer(RENDERER_API::OPENGL, w);

    BINFO("Created renderer: %s", rend->get_name());

    while(!w.should_close()) {
        w.poll_events();
        rend->render();
    }

    delete rend;

    return 0;
}