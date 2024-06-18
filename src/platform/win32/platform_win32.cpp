#include "platform/platform.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "core/logger.h"

window::window(const char *title, u32 width, u32 height): width(width), height(height), internal_handle(nullptr) {
    if(!glfwInit()) {
        FATAL_ERROR("Failed to initialize GLFW");
    }

    // Set window hints (opengl) TODO: move this to a renderer-specific file
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    internal_handle = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if(!internal_handle) {
        FATAL_ERROR("Failed to create window");
    }

    glfwMakeContextCurrent((GLFWwindow*)internal_handle);
}

void window::poll_events() {
    glfwPollEvents();
}

bool window::should_close() {
    return glfwWindowShouldClose((GLFWwindow*)internal_handle);
}

void window::swap_buffers() const {
    glfwSwapBuffers((GLFWwindow*)internal_handle);
}

void window::set_framebuffer_callback(void(*callback)(void*, u32, u32)) {
    glfwSetFramebufferSizeCallback((GLFWwindow*)internal_handle, (GLFWframebuffersizefun)callback);
}

f64 platform_get_absolute_time() {
    return glfwGetTime();
}
