#include "camera.h"

void camera::set_position(f32 x, f32 y, f32 z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

void camera::set_rotation(f32 rotation) {
    this->rotation = rotation;
}
