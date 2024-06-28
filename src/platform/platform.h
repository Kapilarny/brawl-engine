#ifndef PLATFORM_H
#define PLATFORM_H

#include "defines.h"
#include "core/logger.h"
#include "memory/bvector.h"
#include "input.h"

#include <glm/glm.hpp>

class window {
public:
    window(const char* title, u32 width, u32 height);

    void poll_events();
    bool should_close();

    void set_should_close(bool value) const;

    void swap_buffers() const; // TODO: move this to a renderer-specific file
    void set_framebuffer_callback(void (*callback)(void*, u32, u32)); // TODO: move this to a renderer-specific file

    [[nodiscard]] u32 get_width() const { return width; }
    [[nodiscard]] u32 get_height() const { return height; }
private:
    u32 width, height;
    void* internal_handle;
};

class file_handle {
public:
    file_handle() = default;
    ~file_handle();

    bool open(const char* path);
    void close();

    bvector<u8> read_bytes();

    [[nodiscard]] const char* get_path() const { return path; }
    [[nodiscard]] void* get_internal_handle() const { return internal_handle; }

    const char* path;
    void* internal_handle;
};

f64 platform_get_absolute_time();
void platform_sleep(u64 ms);

void platform_log_output(const char* msg, LOG_LEVEL level);

void* platform_get_proc_address_ptr();

// bool platform_input_key_pressed(Key key);
// bool platform_input_key_released(Key key);
bool platform_input_key_down(input_key key);
bool platform_input_key_up(input_key key);
key_state platform_input_get_key_state(input_key key);

glm::vec2 platform_input_get_mouse_position();
bool platform_input_mouse_button_down(mouse_button button);
bool platform_input_mouse_button_up(mouse_button button);
key_state platform_input_get_mouse_button_state(mouse_button button);

#endif //PLATFORM_H
