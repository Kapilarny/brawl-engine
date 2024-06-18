#include "renderer_frontend.h"

#include "core/logger.h"
#include "gl/gl_backend.h"

renderer_frontend* create_renderer(RENDERER_API api, window& window) {
    switch (api) {
        case RENDERER_API::OPENGL:
            return new gl_backend(window);
        default:
            FATAL_ERROR("Unknown renderer!");
    }

    return nullptr;
}
