#ifndef STRING_H
#define STRING_H

#include <stdbool.h>
#include <string.h>

#include "utils/array/array.h"

char* stringGetSubstring(const char* self, int start, int end);

char* stringTrim(const char* self);

Array* stringSplit(const char* self, const char* sepparator);

bool stringContainsChar(const char* self, char c);

void freeSplittedString(Array *array);

// works similarly to strcmp, but will return 0 if the prefix is the beginning of self
int stringComparePrefix(const char *self, const char *prefix);

#endif
