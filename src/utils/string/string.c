#include <stdlib.h>

#include "./string.h"

int _processPosition(int len, int pos) {
  int offset = pos >= 0 ? pos : len - pos;
  if (offset < 0) {
    return 0;
  }
  if (offset >= len) {
    return len-1;
  }
  return offset;
}

char* _getSubstring(const char* str, int len, int first, int last) {
  int offset = _processPosition(len, first);
  int size = _processPosition(len, last) - offset;
  bool isReversed = size < 0;
  size = (size < 0 ? -size : size) + 1;

  char *newString = (char*)malloc(size+1);
  for (int i = 0; i != size; ++i) {
    newString[i] = str[offset + (isReversed ? -i : i)];
  }
  newString[size] = '\0';
  return newString;
}

char* getSubstring(const char* str, int first_index, int last_index) {
  return _getSubstring(str, strlen(str), first_index, last_index);
}

const Array* splitString(const char* str, const char* sepparator);

