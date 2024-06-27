#include "camera.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

camera::camera(window& wnd, f32 x, f32 y, f32 z, f32 rotation) : wnd(wnd), x(x), y(y), z(z), rotation(rotation) {
    update_view();
    update_projection();
}

void camera::update_view() {
    auto view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(x, y, z));
    view = glm::rotate(view, glm::radians(rotation), glm::vec3(0, 0, 1));
    this->view = view;
}

void camera::update_projection() {
    auto projection = glm::perspective(glm::radians(45.0f), (f32)wnd.get_width() / (f32)wnd.get_height(), 0.1f, 100.0f);
    this->projection = projection;
}

void camera::set_position(f32 x, f32 y, f32 z) {
    this->x = x;
    this->y = y;
    this->z = z;

    update_view();
    update_projection(); // TODO: Only update projection if window size changes
}

void camera::set_rotation(f32 rotation) {
    this->rotation = rotation;

    update_view();
    update_projection(); // TODO: Only update projection if window size changes
}
