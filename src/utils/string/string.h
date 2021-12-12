#ifndef STRING_H
#define STRING_H

#include <stdbool.h>
#include <string.h>

#include "utils/array/array.h"

char* stringGetSubstring(const char* self, int start, int end);

char* stringTrim(const char* self);

Array* stringSplit(const char* self, const char* sepparator);

#endif
