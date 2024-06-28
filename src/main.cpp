#include <cmath>
#include <iostream>

#include "core/bclock.h"
#include "core/logger.h"
#include "memory/bstring.h"
#include "platform/platform.h"
#include "renderer/font_renderer.h"
#include "renderer/renderer_2d.h"
#include "renderer/renderer_frontend.h"

int main() {
    window w("Brawl Engine", 1024, 1024);
    auto rend = renderer_2d(w, RENDERER_API::OPENGL);
    rend.set_blending(true);

    BINFO("Created renderer: %s", rend.get_backend_name());

    // Make the clear color red
    glm::vec4 color = {1.0f, 1.0f, 0.0f, 1.0f};
    rend.set_clear_color(color);

    glm::vec2 pos = {0, 1};
    i32 multiplier = 1;

    texture::set_flip_y(true);
    ptr_wrap<texture> container = texture::create("../resources/container.jpg", texture_format::RGB);
    ptr_wrap<texture> awesomeface = texture::create("../resources/awesomeface.png", texture_format::RGBA);

    ptr_wrap<texture> board = texture::create("../resources/chess/board.jpg", texture_format::RGB);

    ptr_wrap pawn = texture::create("../resources/chess/bP.png", texture_format::RGB);


    font_renderer font(rend.get_backend(), "../resources/cursecasual.ttf");

    u64 frame_count = 0;
    f64 target_frame_time = 1.0 / 60.0 / 2; // I dont get it why i have to divide it by 2 but it works so not complaining
    bclock delta_clock; // Classic me, forgot that i implemented a clock class

    camera_2d& cam = rend.get_camera();

    while(!w.should_close()) {
        // Calculate delta time
        f64 delta_time = delta_clock.update();
        delta_clock.start();

        w.poll_events();

        rend.begin();

        rend.draw_quad({w.get_width() / 2, w.get_height() / 2}, {w.get_width(), w.get_height()}, board.get()); // Draw the board

        // Frame Counter
        char buffer[256] = {0};
        bzero_memory(buffer, 256 * sizeof(char));
        f64 fps = 1.0 / delta_time;
        bstrfmt(buffer, "FPS: %.0f", fps);
        font.render_text((char*)&buffer, {0, w.get_height()-20}, .5f, {0, 0, 0});

        font.render_text("Brawl Engine", {10, 10}, 1, {0, 0, 0});
        rend.end();

        // Frame Cap
        f64 frame_time = platform_get_absolute_time() - delta_clock.get_start_time();
        if(frame_time < target_frame_time) {
            platform_sleep((u32)((target_frame_time - frame_time) * 1000.0));
        }

        frame_count++;
    }

    return 0;
}