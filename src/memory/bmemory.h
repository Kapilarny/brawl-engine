#ifndef GMEMORY_H
#define GMEMORY_H

#include "defines.h"

void bzero_memory(void* memory, u64 size);
void bcopy_memory(void* dest, void* src, u64 size);
void bset_memory(void* memory, u8 value, u64 size);

#endif //GMEMORY_H
