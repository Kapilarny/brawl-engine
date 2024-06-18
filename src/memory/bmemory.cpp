#include "bmemory.h"

void bzero_memory(void *memory, u64 size) {
    u8 *byte = (u8 *)memory;
    for (u64 i = 0; i < size; i++) {
        *byte++ = 0;
    }
}