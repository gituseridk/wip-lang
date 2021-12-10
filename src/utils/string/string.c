#include <stdlib.h>
#include <ctype.h>

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

int _getTrimmedStringStart(const char *str) {
  int result = 0;
  while(isspace(str[result])) ++result;
  return result;
}

int _getTrimmedStringEnd(const char *str) {
  int result = strlen(str);
  while (isspace(str[--result]));
  return result;
}

char* trimString(const char *str) {
  return getSubstring(str, _getTrimmedStringStart(str), _getTrimmedStringEnd(str));
}

Array* splitString(const char* str, const char* sepparator) {
  int sepparator_length = strlen(sepparator);
  Array *result = newArray(0, sizeof(char*), NULL);
  const char *part_start = str;
  while (true) {
    char *part_end = strstr(part_start, sepparator);
    if (part_end == NULL) {
      push(result, part_start);
      break;
    }
    int len = part_end - part_start;
    char *part = malloc(len + 1);
    memcpy(part, part_start, len);
    part[len] = '\0';

    push(result, part);

    free(part);

    part_start = part_end + sepparator_length;
  }
  return result;
}

