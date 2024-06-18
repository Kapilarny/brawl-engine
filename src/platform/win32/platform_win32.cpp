#include "logger.h"
#include "GLFW/glfw3.h"
#include "platform/platform.h"

window::window(const char *title, u32 width, u32 height): width(width), height(height), internal_handle(nullptr) {
    if(!glfwInit()) {
        FATAL_ERROR("Failed to initialize GLFW");
    }

    // Set window hints (vulkan) TODO: move this to a renderer-specific file
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

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
