#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "./string.h"

const String newString(const char* value) {
  return (String) {
    .value = value,
    .length = strlen(value),
  };
}

const char *getStringValue(const String *self) {
  return self->value;
}

const unsigned getStringLength(const String *self) {
  return self->length;
}

const int findSubstring(const String *self, String substring) {
  char *start = strstr(self->value, substring.value);
  if (start == NULL) {
    return -1;
  }
  return start - self->value;
}

const bool isStringsEq(String a, String b) {
  return !strcmp(a.value, b.value);
}

const Array splitString(const String *self, const String separator) {
  // !TODO implementation
  assert(0);
  Array result = newArray(1, sizeof(String), (const String[]){*self});
  return result;
}
