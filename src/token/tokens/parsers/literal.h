#include <stdio.h>
#include <string.h>

const char *LITERAL_CHARS = "0123456789";

bool isLiteralChar(char c) {
  return strchr(LITERAL_CHARS, c) != NULL;
}

CheckIf(literal, token, size) {
  if (isLiteralChar(token[size - 1])) {
    return TOKEN_CHECK_RESULT_VALID;
  }
  if (size > 1 && isLiteralChar(token[size - 2])) {
    return TOKEN_CHECK_RESULT_ENDED;
  }
  return TOKEN_CHECK_RESULT_INVALID;
}
