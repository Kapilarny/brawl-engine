#ifndef PLATFORM_H
#define PLATFORM_H

#include "defines.h"
#include "memory/bvector.h"

class window {
public:
    window(const char* title, u32 width, u32 height);

    void poll_events();
    bool should_close();

    void swap_buffers() const; // TODO: move this to a renderer-specific file
    void set_framebuffer_callback(void (*callback)(void*, u32, u32)); // TODO: move this to a renderer-specific file

    [[nodiscard]] u32 get_width() const { return width; }
    [[nodiscard]] u32 get_height() const { return height; }
private:
    u32 width, height;
    void* internal_handle;
};

f64 platform_get_absolute_time();

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

#endif //PLATFORM_H
