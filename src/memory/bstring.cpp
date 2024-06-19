#include "bstring.h"

#include "bmemory.h"

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