#ifndef BSTRING_H
#define BSTRING_H

#include "defines.h"

u64 bstrlen(const char* str);

void bstrcat(char* dest, char* src);

bool bstrfmt(char* dest, const char* fmt, ...);

#endif //BSTRING_H
