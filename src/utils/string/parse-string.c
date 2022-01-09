#include <stdlib.h>
#include <stdio.h>

#include "./string.h"

static char chopSpecialChar(const char *src) {
  if (src[0] != '\\') {
    return 0;
  }

  switch (src[1])
  {
  case 'n':
    return '\n';
  case 't':
    return '\t';
  case 'v':
    return '\v';
  case 'b':
    return '\b';
  case 'r':
    return '\r';
  case 'f':
    return '\f';
  case 'a':
    return '\a';
  case '\\':
    return '\\';
  case '?':
    return '\?';
  case '"':
    return '\"';
  
  default:
    return 0;
  }
}

int parseString(const char *src, char **result) {
  int src_size = strlen(src) - 2;
  *result = malloc(sizeof(char) * src_size);
  unsigned offset = 0;
  for (const char *i = (src + 1); (i - src) + 1 < src_size;) {
    char new_char = chopSpecialChar(i);
    if (new_char == 0) {
      (*result)[offset++] = *i;
      ++i;
      continue;
    }
    (*result)[offset++] = new_char;
    i += 2;
  }

  (*result)[offset++] = 0;

  return offset + 1;
}
