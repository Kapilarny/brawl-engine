#include "bstring.h"

#include <cstdarg>
#include <cstdio> // TODO: remove this

#include "bmemory.h"
#include "core/logger.h"

void bstrcat(char* dest, char* src) {
    // copy the string
    bcopy_memory(dest + bstrlen(dest), src, bstrlen(src)+1); // we also will copy the null-terminator
}

u64 bstrlen(const char *str) {
    int idx = 0;
    while(str[idx] != '\0') {
        idx++;
    }

    return idx;
}

bool bstrfmt(char* dest, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vsprintf(dest, fmt, args);
    va_end(args);

    return true;
}