#include <cmath>
#include <iostream>

#include "core/bclock.h"
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
    glm::vec4 color = {1.0f, 1.0f, 0.0f, 1.0f};
    rend.set_clear_color(color);

    glm::vec2 pos = {0, 1};
    i32 multiplier = 1;

    texture::set_flip_y(true);
    ptr_wrap<texture> container = texture::create("../resources/container.jpg", texture_format::RGB);
    ptr_wrap<texture> awesomeface = texture::create("../resources/awesomeface.png", texture_format::RGBA);

    u64 frame_count = 0;
    f64 target_frame_time = 1.0 / 60.0;
    bclock delta_clock; // Classic me, forgot that i implemented a clock class

    f64 speed = 3.0;

    while(!w.should_close()) {
        // Calculate delta time
        delta_clock.update();
        f64 delta_time = delta_clock.get_elapsed();
        delta_clock.start();

        w.poll_events();

        // Input
        if(platform_input_key_down(Key::ESCAPE)) {
            w.set_should_close(true);
            continue;
        }

        if(platform_input_key_down(Key::W)) {
            pos.y += speed * delta_time;
        }

        if(platform_input_key_down(Key::S)) {
            pos.y -= speed * delta_time;
        }

        if(platform_input_key_down(Key::A)) {
            pos.x -= speed * delta_time;
        }

        if(platform_input_key_down(Key::D)) {
            pos.x += speed * delta_time;
        }

        rend.begin();

        camera& cam = rend.get_camera();
        // cam.set_position(0, 0, cam.get_z() + (multiplier * 3 * delta_time));

        // rend.draw_quad({-pos.x, pos.y + .5f}, {1, 1}, container.get());
        // rend.draw_quad({pos.x, pos.y - .5f}, {1, 1}, awesomeface.get());

        rend.draw_quad(pos, {1, 1}, container.get(), 45);
        rend.draw_quad({0, 0}, {1, 1}, {1, 0, 0, 1});

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