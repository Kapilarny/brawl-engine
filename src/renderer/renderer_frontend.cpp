#include "renderer_frontend.h"

#include "core/logger.h"
#include "gl/gl_backend.h"

static RENDERER_API API{};

renderer_frontend* create_renderer(RENDERER_API api, window& window) {
    API = api;

    switch (api) {
        case RENDERER_API::OPENGL:
            return new gl_backend(window);
        default:
            FATAL_ERROR("Unknown renderer!");
    }

    return nullptr;
}

RENDERER_API get_renderer_api() {
    return RENDERER_API::OPENGL;
}