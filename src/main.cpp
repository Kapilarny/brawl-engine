#include <cmath>
#include <iostream>

#include "core/logger.h"
#include "platform/platform.h"
#include "renderer/renderer_2d.h"
#include "renderer/renderer_frontend.h"

int main() {
    window w("Brawl Engine", 800, 600);
    auto rend = renderer_2d(w, RENDERER_API::OPENGL);
    rend.set_blending(true);

    BINFO("Created renderer: %s", rend.get_backend_name());

    // Make the clear color red
    glm::vec4 color = {1.0f, 0.0f, 0.0f, 1.0f};
    rend.set_clear_color(color);

    glm::vec2 pos = {0, 1};
    i32 multiplier = 1;

    texture::set_flip_y(true);
    ptr_wrap<texture> container = create_texture("../resources/container.jpg", texture_format::RGB);
    ptr_wrap<texture> awesomeface = create_texture("../resources/awesomeface.png", texture_format::RGBA);

    f64 last_time = platform_get_absolute_time();
    u64 frame_count = 0;

    f64 target_frame_time = 1.0 / 60.0;
    while(!w.should_close()) {
        // Calculate delta time
        f64 current_time = platform_get_absolute_time();
        f64 delta_time = current_time - last_time;
        last_time = current_time;

        w.poll_events();

        color.g = (f32)sin(platform_get_absolute_time()) / 2.0f + 0.5f;
        rend.set_clear_color(color);

        if(pos.x >= 1.5 || pos.x <= -1.5) {
            multiplier *= -1;
        }

        pos.x += 3 * delta_time * multiplier;

        rend.begin();

        camera& cam = rend.get_camera();
        // cam.set_position(0, 0, cam.get_z() + (multiplier * 3 * delta_time));

        for(int i = 0; i < 10; i++) {
            for(int j = 0; j < 10; j++) {
                rend.draw_quad({pos.x + i * 0.25, pos.y - j * 0.25}, {0.2, 0.2}, container.get());
            }
        }

        // rend.draw_quad({-pos.x, pos.y + .5f}, {1, 1}, container.get());
        // rend.draw_quad({pos.x, pos.y - .5f}, {1, 1}, awesomeface.get());

        // rend.draw_quad({1, 0}, {1, 1}, container.get());

        rend.end();

        // Frame Cap
        // f64 frame_time = platform_get_absolute_time() - current_time;
        // if(frame_time < target_frame_time) {
        //     platform_sleep((u32)((target_frame_time - frame_time) * 1000.0));
        // }
        //
        frame_count++;
    }

    return 0;
}