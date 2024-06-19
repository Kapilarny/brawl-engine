#include "bmemory.h"

void bzero_memory(void *memory, u64 size) {
    u8 *byte = (u8 *)memory;
    for (u64 i = 0; i < size; i++) {
        *byte++ = 0;
    }
}

void bcopy_memory(void* dest, void* src, u64 size) {
    u8* byte = (u8*)dest;
    u8* copy = (u8*)src;
    for(int i = 0; i < size; i++) {
        byte[i] = copy[i];
    }
}