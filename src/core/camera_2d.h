//
// Created by user on 29.06.2024.
//

#ifndef CAMERA_2D_H
#define CAMERA_2D_H
#include <glm/glm.hpp>

#include "defines.h"
#include "renderer/renderer_frontend.h"

class camera_2d {
public:
    camera_2d() = default;
    explicit camera_2d(renderer_frontend* rend, f32 x = 0, f32 y = 0, f32 rotation = 0);
    ~camera_2d() = default;


    void set_position(f32 x, f32 y);
    void set_rotation(f32 rotation);

    void update_view();
    void update_projection();

    [[nodiscard]] f32 get_x() const { return x; }
    [[nodiscard]] f32 get_y() const { return y; }

    [[nodiscard]] glm::mat4 get_view() const { return view; }
    [[nodiscard]] glm::mat4 get_projection() const { return projection; }

    [[nodiscard]] f32 get_rotation() const { return rotation; }
public:
    glm::mat4 view{};
    glm::mat4 projection{};

    renderer_frontend* rend;
    f32 x{}, y{};
    f32 rotation{};
};

#endif //CAMERA_2D_H
