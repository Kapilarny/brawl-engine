#ifndef RENDERER_FRONTEND_H
#define RENDERER_FRONTEND_H

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include "defines.h"
#include "vertex_array.h"
#include "memory/ptr_wrap.h"
#include "platform/platform.h"

enum class RENDERER_API {
    OPENGL,
    VULKAN,
};

class renderer_frontend {
public:
    explicit renderer_frontend(window& window) : wnd(window) {}
    virtual ~renderer_frontend() = default;

    virtual void begin_render() = 0;
    virtual void end_render() = 0;

    virtual void set_clear_color(glm::vec4& color) = 0;

    virtual void set_blending(bool blend) = 0;
    virtual void draw_indexed(vertex_array* vertex_array, u32 index_count) = 0;
    virtual void draw_arrays(vertex_array* vertex_array, u32 count) = 0;

    virtual void set_viewport(u32 x, u32 y, u32 width, u32 height) = 0;
    virtual glm::vec2 get_viewport() = 0;
    virtual const char* get_name() = 0;
protected:
    window& wnd;
};

/**
 * This function creates a renderer frontend based on the API type.
 * @param api Type of renderer
 * @param window Window to render to
 * @return Pointer to renderer frontend
 */
renderer_frontend* create_renderer(RENDERER_API api, window& window);

RENDERER_API get_renderer_api();

#endif //RENDERER_FRONTEND_H
