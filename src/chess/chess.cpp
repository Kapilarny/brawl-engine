//
// Created by user on 29.06.2024.
//

#include "chess.h"

#include "board.h"
#include "core/bclock.h"
#include "core/logger.h"
#include "memory/bstring.h"
#include "platform/platform.h"
#include "renderer/font_renderer.h"
#include "renderer/renderer_2d.h"
#include "renderer/renderer_frontend.h"


void chess_example() {
    window w("Brawl Engine", 1024, 1024);
    auto rend = renderer_2d(w, RENDERER_API::OPENGL);
    rend.set_blending(true);

    BINFO("Created renderer: %s", rend.get_backend_name());

    texture::set_flip_y(true);
    // ptr_wrap<texture> board = texture::create("../resources/chess/board.jpg", texture_format::RGB);
    ptr_wrap the_rook = texture::create("../resources/chess/wR.png", texture_format::RGBA); // THE ROOK

    font_renderer font(rend.get_backend(), "../resources/cursecasual.ttf");

    f64 target_frame_time = 1.0 / 60.0 / 2; // I dont get it why i have to divide it by 2 but it works so not complaining
    bclock delta_clock; // Classic me, forgot that i implemented a clock class

    board board;

    while(!w.should_close()) {
        // Calculate delta time
        f64 delta_time = delta_clock.update();
        delta_clock.start();
        w.poll_events();

        board.update(); // Update the board

        rend.begin();

        board.draw_board(rend, font);

        // rend.draw_quad({0, 0}, {w.get_width(), w.get_height()}, board.get()); // Draw the board

        // for(int i = 0; i < 8; i++) {
        //     rend.draw_quad({-7 + i * 130, -10 + i * 130}, {130, 130}, the_rook.get()); // I spent 15 minutes fine tuning the position stuff lmfao
        // }

        font.render_text("brawl engine (c)", {10, 10}, 1, {sin(platform_get_absolute_time()), -sin(platform_get_absolute_time()), sin(platform_get_absolute_time())});

        rend.end();

        // Frame Cap
        f64 frame_time = platform_get_absolute_time() - delta_clock.get_start_time();
        if(frame_time < target_frame_time) {
            platform_sleep((u32)((target_frame_time - frame_time) * 1000.0));
        }
    }
}
