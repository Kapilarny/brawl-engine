#ifndef CAMERA_H
#define CAMERA_H
#include "defines.h"

// TODO: ECS'ify this

class camera {
public:
    camera() {}
    ~camera() {}

    void set_position(f32 x, f32 y, f32 z);
    void set_rotation(f32 rotation);

    [[nodiscard]] f32 get_x() const { return x; }
    [[nodiscard]] f32 get_y() const { return y; }
    [[nodiscard]] f32 get_z() const { return z; }

    [[nodiscard]] f32 get_rotation() const { return rotation; }
private:
    f32 x, y, z;
    f32 rotation;
};



#endif //CAMERA_H
