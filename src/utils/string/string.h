#ifndef STRING_H
#define STRING_H

#include <stdbool.h>
#include <string.h>

#include "utils/array/array.h"

char* getSubstring(const char* str, int start, int end);

Array splitString(const char* str, const char* sepparator);

#endif
