//
// Created by Matylda on 18.06.2024.
//

#include "gl_backend.h"

#include <glad/gl.h>

#include "core/logger.h"
#include "GLFW/glfw3.h" // glfwGetProcAddress TODO: make this a platform thing
#include "memory/bvector.h"

void on_resize(void* internal, u32 width, u32 height) {
    glViewport(0, 0, width, height);
}

gl_backend::gl_backend(window &window): renderer_frontend(window) {
    i32 version = gladLoadGL(glfwGetProcAddress);
    if(!version) {
        FATAL_ERROR("Failed to initialize OpenGL context!");
    }

    BINFO("Loaded OpenGL %d.%d", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

    glViewport(0, 0, window.get_width(), window.get_height());
    window.set_framebuffer_callback(on_resize);

    shader.create("../shaders/test_shader.vert", "../shaders/test_shader.frag");

    f32 vertices[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
       -0.5f, -0.5f, 0.0f,  // bottom left
       -0.5f,  0.5f, 0.0f   // top left
   };

    u32 indices[] = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    // Generate buffers
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    glGenVertexArrays(1, &vao);

    // Bind VAO, bind and set VBO, configure vertex attributes
    glBindVertexArray(vao);

    // Copy vertices to VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Copy indices to EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32), (void*)0);
    glEnableVertexAttribArray(0);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); TODO: Add wireframe mode
}

gl_backend::~gl_backend() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);

    BINFO("Destroyed GL Backend!");
}

void gl_backend::render() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader.use();
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    wnd.swap_buffers();
}

const char *gl_backend::get_name() {
    return "OpenGL";
}
