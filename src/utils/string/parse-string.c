#include <stdlib.h>
#include <stdio.h>

#include "./string.h"

static const char *chopSpecialChar(const char *src) {
  if (src[0] != '\\') {
    return NULL;
  }

  if (stringContainsChar(SPECIAL_CHARACTERS, src[1])) {
    return src[1];
  }

  return NULL;
}

int parseString(const char *src, char **result) {
  int src_size = strlen(src) - 2;
  *result = malloc(sizeof(char) * src_size);
  unsigned offset = 0;
  for (const char *i = (src + 1); (i - src) < src_size;) {
    const char *new_offset = chopSpecialChar(i);
    if (new_offset == NULL) {
      (*result)[offset++] = *i;
      ++i;
      continue;
    }
    (*result)[offset++] = *new_offset;
    i += 2;
  }

  (*result)[offset++] = 0;

  return offset + 1;
}
