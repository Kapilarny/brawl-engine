#ifndef PLATFORM_H
#define PLATFORM_H

#include "defines.h"

class window {
public:
    window(const char* title, u32 width, u32 height);

    void poll_events();
    bool should_close();
private:
    u32 width, height;
    void* internal_handle;
};

#endif //PLATFORM_H
