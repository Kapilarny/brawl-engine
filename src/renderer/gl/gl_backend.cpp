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

    // Load shaders
    shader.create("../shaders/test_shader.vert", "../shaders/test_shader.frag");

    float vertices[] = {
        // positions         // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
       -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
       -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
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

    // Vertex Attributes
    i32 stride = 8 * sizeof(f32);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);

    // Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(f32)));
    glEnableVertexAttribArray(1);

    // Texture
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(f32)));
    glEnableVertexAttribArray(2);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); TODO: Add wireframe mode

    stbi_set_flip_vertically_on_load(true); // Flip the textures vertically

    // Load textures
    container.load_file("../resources/container.jpg", texture_format::RGB);
    face.load_file("../resources/awesomeface.png", texture_format::RGBA);

    // Set proper texture units
    shader.use(); // Don't forget to activate the shader before setting uniforms!
    shader.set_i32("texture1", 0);
    shader.set_i32("texture2", 1);
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

    // Bind textures
    container.bind(0);
    face.bind(1);

    shader.use();

    auto model = glm::mat4(1.0f);
    auto view = glm::mat4(1.0f);
    auto projection = glm::mat4(1.0f);

    model = glm::rotate(model, (f32)platform_get_absolute_time(), glm::vec3(0.5f, 1.0f, 0.0f));
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    projection = glm::perspective(glm::radians(45.0f), (f32)wnd.get_width() / (f32)wnd.get_height(), 0.1f, 100.0f);

    shader.set_mat4("model", model);
    shader.set_mat4("view", view);
    shader.set_mat4("projection", projection);

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // glDrawArrays(GL_TRIANGLES, 0, 3);

    wnd.swap_buffers();
}

const char *gl_backend::get_name() {
    return "OpenGL";
}
