#ifndef STRING_H
#define STRING_H

#include<stdbool.h>

#include "utils/array/array.h"

typedef struct {
  const char *value;
  unsigned length;
} String;

const String newString(const char *value);

const char *getStringValue(const String *self);
const unsigned getStringLength(const String *self);
const int findSubstring(const String *self, String substring);
const bool isStringsEq(String a, String b);
const Array splitString(const String *self, String separator);

#endif