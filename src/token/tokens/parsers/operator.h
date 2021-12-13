#include <stdio.h>
#include <string.h>

const char *OPERATORS = "+-/*=";

bool isOperatorChar(char c) {
  return c != 0 && strchr(OPERATORS, c) != NULL;
}

CheckIf(operator, token, size) {
  if (isOperatorChar(token[size - 1])) {
    return TOKEN_CHECK_RESULT_VALID;
  }
  if (size > 1 && isOperatorChar(token[size - 2])) {
    return TOKEN_CHECK_RESULT_ENDED;
  }
  return TOKEN_CHECK_RESULT_INVALID;
}
