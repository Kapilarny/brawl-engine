#include "platform/platform.h"

#define GLFW_INCLUDE_NONE
#include <cstdio>
#include <GLFW/glfw3.h>

#include <windows.h>
#include <glm/vec2.hpp>

#include "core/logger.h"

// TODO: Cant make this work yet, need to figure it out more properly

// i32 curr_keys[GLFW_KEY_LAST] = {};
// i32 last_keys[GLFW_KEY_LAST] = {};
// void key_callback(GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mods) {
//     last_keys[key] = curr_keys[key];
//     curr_keys[key] = action;
// }


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
    // glfwSetKeyCallback((GLFWwindow*)internal_handle, key_callback);
}

void window::poll_events() {
    glfwPollEvents();
}

bool window::should_close() {
    return glfwWindowShouldClose((GLFWwindow*)internal_handle);
}

void window::set_should_close(bool value) const {
     glfwSetWindowShouldClose((GLFWwindow*)internal_handle, value);
}

void window::swap_buffers() const {
    glfwSwapBuffers((GLFWwindow*)internal_handle);
}

void window::set_framebuffer_callback(void(*callback)(void*, u32, u32)) {
    glfwSetFramebufferSizeCallback((GLFWwindow*)internal_handle, (GLFWframebuffersizefun)callback);
}

file_handle::~file_handle() {
    close();
}

bool file_handle::open(const char *path) {
    if(internal_handle) FATAL_ERROR("Reopening on an unclosed file handle!");

    // use windows api to open file
    internal_handle = fopen(path, "rb");
    if(!internal_handle) {
        BERROR("Failed to open file: %s", path);
        return false;
    }

    return true;
}

void file_handle::close() {
    if(internal_handle) fclose((FILE*)internal_handle);
    internal_handle = nullptr;
}

bvector<u8> file_handle::read_bytes() {
    if(!internal_handle) FATAL_ERROR("Reading a null file!");

    // Get file size
    fseek((FILE*)internal_handle, 0, SEEK_END);
    u32 size = ftell((FILE*)internal_handle);
    rewind((FILE*)internal_handle);

    bvector<u8> data(size);

    // Read file
    fread(data.data(), 1, size, (FILE*)internal_handle);

    return data;
}

void platform_log_output(const char* msg, LOG_LEVEL level) {
    constexpr u8 level_colors[6] = {64, 4, 6, 2, 1, 8};

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, level_colors[(u32)level]);

    WriteConsoleA(hConsole, msg, strlen(msg), nullptr, nullptr);
}

f64 platform_get_absolute_time() {
    return glfwGetTime();
}

void platform_sleep(u64 ms) {
    Sleep(ms);
}

void* platform_get_proc_address_ptr() {
    return (void*)glfwGetProcAddress;
}

bool platform_input_key_down(input_key key) {
    return glfwGetKey((GLFWwindow*)glfwGetCurrentContext(), (i32)key) == GLFW_PRESS;
}

bool platform_input_key_up(input_key key) {
    return glfwGetKey((GLFWwindow*)glfwGetCurrentContext(), (i32)key) == GLFW_RELEASE;
}

key_state platform_input_get_key_state(input_key key) {
    return (key_state)glfwGetKey((GLFWwindow*)glfwGetCurrentContext(), (i32)key);
}

glm::vec2 platform_input_get_mouse_position() {
    f64 x, y;
    glfwGetCursorPos((GLFWwindow*)glfwGetCurrentContext(), &x, &y);
    return {(f32)x, (f32)y};
}

bool platform_input_mouse_button_down(mouse_button button) {
    return glfwGetMouseButton((GLFWwindow*)glfwGetCurrentContext(), (i32)button) == GLFW_PRESS;
}

bool platform_input_mouse_button_up(mouse_button button) {
    return glfwGetMouseButton((GLFWwindow*)glfwGetCurrentContext(), (i32)button) == GLFW_RELEASE;
}

key_state platform_input_get_mouse_button_state(mouse_button button) {
    return (key_state)glfwGetMouseButton((GLFWwindow*)glfwGetCurrentContext(), (i32)button);
}