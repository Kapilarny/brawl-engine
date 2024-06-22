#ifndef RENDERER_2D_H
#define RENDERER_2D_H

#include "renderer_frontend.h"

class renderer_2d {
public:
    renderer_2d(window& window, const RENDERER_API api) : renderer(create_renderer(api, window)) {}

    void begin();
    void end();

    const char* get_backend_name() const { return renderer->get_name(); }

    void set_clear_color(glm::vec4& color) const;
private:
    ptr_wrap<renderer_frontend> renderer;
};

#endif //RENDERER_2D_H
