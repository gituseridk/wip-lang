#include <stdio.h>

static bool isIdentifierChar(char c) {
  return (c > 64 && c < 91) || (c >  96 && c < 123);
}

CheckIf(identifier, token, size) {
  if (isIdentifierChar(token[size - 1])) {
    return TOKEN_CHECK_RESULT_VALID;
  }
  if (size > 1 && isIdentifierChar(token[size - 2])) {
    return TOKEN_CHECK_RESULT_ENDED;
  }
  return TOKEN_CHECK_RESULT_INVALID;
}
