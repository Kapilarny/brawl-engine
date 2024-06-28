//
// Created by user on 29.06.2024.
//

#include "camera_2d.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "renderer/renderer_frontend.h"

camera_2d::camera_2d(renderer_frontend* rend, f32 x, f32 y, f32 rotation) : rend(rend) {
    set_position(x, y);
}

void camera_2d::set_position(f32 x, f32 y) {
    this->x = x;
    this->y = y;

    glm::vec2 size = rend->get_viewport();
    projection = glm::ortho(0.0f, size.x, 0.0f, size.y);
}

void camera_2d::set_rotation(f32 rotation) {
    this->rotation = rotation;

    // projection = glm::rotate(projection, glm::radians(rotation), glm::vec3(0, 0, 1));
}

void camera_2d::update_view() {

}

void camera_2d::update_projection() {

}
