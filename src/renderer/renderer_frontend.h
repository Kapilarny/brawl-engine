#ifndef RENDERER_FRONTEND_H
#define RENDERER_FRONTEND_H

#include "defines.h"
#include "platform/platform.h"

enum class RENDERER_API {
    OPENGL,
    VULKAN,
};

class renderer_frontend {
public:
    explicit renderer_frontend(window& window) : wnd(window) {}
    virtual ~renderer_frontend() = default;

    virtual void render() = 0;
    virtual void draw_tex_quad(f32 x, f32 y, u32 texture_id) = 0; // TODO: remove this, this is for ECS testing
    virtual const char* get_name() = 0;
protected:
    window& wnd;
};

/**
 * This function creates a renderer frontend based on the API type. IMPORTANT: You need to `delete` the renderer_frontend object after you're done with it.
 * @param api Type of renderer
 * @param window Window to render to
 * @return Pointer to renderer frontend
 */
renderer_frontend* create_renderer(RENDERER_API api, window& window);

#endif //RENDERER_FRONTEND_H
