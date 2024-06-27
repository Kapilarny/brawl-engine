#ifndef CAMERA_H
#define CAMERA_H

#include "defines.h"
#include "platform/platform.h"

#include <glm/glm.hpp>

// TODO: ECS'ify this

class camera {
public:
    explicit camera(window& wnd, f32 x = 0, f32 y = 0, f32 z = 0, f32 rotation = 0);
    ~camera() = default;

    void set_position(f32 x, f32 y, f32 z);
    void set_rotation(f32 rotation);

    void update_view();
    void update_projection();

    [[nodiscard]] f32 get_x() const { return x; }
    [[nodiscard]] f32 get_y() const { return y; }
    [[nodiscard]] f32 get_z() const { return z; }

    [[nodiscard]] glm::mat4 get_view() const { return view; }
    [[nodiscard]] glm::mat4 get_projection() const { return projection; }

    [[nodiscard]] f32 get_rotation() const { return rotation; }
private:
    window& wnd;
    glm::mat4 view{};
    glm::mat4 projection{};

    f32 x, y, z;
    f32 rotation;
};



#endif //CAMERA_H
