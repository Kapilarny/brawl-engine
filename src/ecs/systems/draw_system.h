#ifndef DRAW_SYSTEM_H
#define DRAW_SYSTEM_H
#include "ecs/isystem.h"
#include "renderer/renderer_frontend.h"

// TODO: Make this a system that draws entities with a transform and texture_2d component

class draw_system : public isystem {
public:
    draw_system(renderer_frontend& renderer) : renderer(renderer) {}

    void draw();
private:
    renderer_frontend& renderer;
};

#endif //DRAW_SYSTEM_H
