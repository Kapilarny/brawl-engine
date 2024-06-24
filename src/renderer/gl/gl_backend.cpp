#include "gl_backend.h"

#include <stbi_image.h>
#include <glad/gl.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "core/logger.h"
#include "memory/bvector.h"

void on_resize(void* internal, u32 width, u32 height) {
    glViewport(0, 0, width, height);
}

gl_backend::gl_backend(window &window): renderer_frontend(window) {
    i32 version = gladLoadGL((GLADloadfunc)platform_get_proc_address_ptr());
    if(!version) {
        FATAL_ERROR("Failed to initialize OpenGL context!");
    }

    BINFO("Loaded OpenGL %d.%d", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

    glViewport(0, 0, window.get_width(), window.get_height());
    window.set_framebuffer_callback(on_resize);
}

gl_backend::~gl_backend() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);

    BINFO("Destroyed GL Backend!");
}

void gl_backend::begin_render() {
    ASSERT(!drawing, "Already drawing!");

    glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);
    glClear(GL_COLOR_BUFFER_BIT);

    drawing = true;
}

void gl_backend::end_render() {
    ASSERT(drawing, "Not drawing!");

    wnd.swap_buffers();

    drawing = false;
}

void gl_backend::set_viewport(u32 x, u32 y, u32 width, u32 height) {
    glViewport(x, y, width, height);
}

void gl_backend::draw_indexed(vertex_array *vertex_array, u32 index_count) {
    vertex_array->bind();
    u32 count = index_count ? index_count : vertex_array->get_index_buffer()->get_count();
    glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, nullptr);
}

const char *gl_backend::get_name() {
    return "OpenGL";
}
