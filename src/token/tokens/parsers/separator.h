#include <stdio.h>
#include <string.h>

const char *SEPARATOR = ",.;:";

bool isSeparatorChar(char c) {
  return strchr(SEPARATOR, c) != NULL;
}

CheckIf(separator, token, size) {
  if (isSeparatorChar(token[size - 1])) {
    return TOKEN_CHECK_RESULT_VALID;
  }
  if (size > 1 && isSeparatorChar(token[size - 2])) {
    return TOKEN_CHECK_RESULT_ENDED;
  }
  return TOKEN_CHECK_RESULT_INVALID;
}
