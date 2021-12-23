#include <stdlib.h>
#include <ctype.h>

#include "./string.h"

static int processPosition(int len, int pos) {
  int offset = pos >= 0 ? pos : len - pos;
  if (offset < 0) return 0;
  if (offset >= len) return len-1;
  return offset;
}

static char* getSubstringWithLen(const char* str, int len, int first, int last) {
  int offset = processPosition(len, first);
  int size = processPosition(len, last) - offset;
  bool isReversed = size < 0;
  size = (size < 0 ? -size : size) + 1;

  char *newString = (char*)malloc(size+1);
  for (int i = 0; i != size; ++i) {
    newString[i] = str[offset + (isReversed ? -i : i)];
  }
  newString[size] = '\0';
  return newString;
}

char* stringGetSubstring(const char* self, int first_index, int last_index) {
  return getSubstringWithLen(self, strlen(self), first_index, last_index);
}

static int getTrimmedStringStart(const char *self) {
  int result = 0;
  while(isspace(self[result])) ++result;
  return result;
}

static int getTrimmedStringEnd(const char *str) {
  int result = strlen(str);
  while (isspace(str[--result]));
  return result;
}

char* stringTrim(const char *self) {
  return stringGetSubstring(self, getTrimmedStringStart(self), getTrimmedStringEnd(self));
}

Array* stringSplit(const char* self, const char* sepparator, bool with_empty) {
  int sepparator_length = strlen(sepparator);
  Array *result = createEmptyArray(1, sizeof(char*));
  const char *part_start = self;
  while (true) {
    char *part_end = strstr(part_start, sepparator);
    if (part_end == NULL) {
      int len = strlen(part_start);
      if (len != 0 || with_empty) {
        char *part = malloc(len + 1);
        memcpy(part, part_start, len);
        part[len] = '\0';
        arrayPush(result, &part);
      }
      break;
    }
    int len = part_end - part_start;
    if (len == 0 && !with_empty) {
      part_start = part_end + sepparator_length;
      continue;
    }
    char *part = malloc(len + 1);
    memcpy(part, part_start, len);
    part[len] = '\0';

    arrayPush(result, &part);

    part_start = part_end + sepparator_length;
  }
  return result;
}

static void freeSplittedStringElement(void *self, void *element, int index, const Array *arr) {
  free(*(char**)element);
}

void freeSplittedString(Array *array) {
  arrayForEach(array, freeSplittedStringElement, NULL);
  arrayFree(array);
}

bool stringContainsChar(const char* self, char c) {
  return c != 0 && strchr(self, c) != NULL;
}

int stringComparePrefix(const char *self, const char *prefix) {
  while(*prefix) {
    if(*prefix != *self) {
      return *self - *prefix;
    }
    ++prefix;
    ++self;
  }
  return 0;
}
