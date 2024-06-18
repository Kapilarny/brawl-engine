#ifndef PLATFORM_H
#define PLATFORM_H

#include "defines.h"

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

#endif //PLATFORM_H
