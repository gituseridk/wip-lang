#include <stdio.h>

char* chopFloatTail(char *token_start) {
  char *token_end = token_start;
  if (*token_end != '.' && *token_end != 'f') {
    return NULL;
  }
  if (*token_end == 'f') {
    return token_end + 1;
  }
  ++token_end;

  while (
    stringContainsChar(NOT_ZERO_DIGITS, *token_end) ||
    stringContainsChar(ZERO_DIGIT, *token_end)
  ) ++token_end;

  return token_end;
}

ChopToken(literal_float, token_start) {
  if (stringContainsChar(ZERO_DIGIT, *token_start)) {
    return chopFloatTail(token_start + 1);
  }
  if (*token_start == '.') {
    return chopFloatTail(token_start);
  }

  if (!stringContainsChar(NOT_ZERO_DIGITS, *token_start)) {
    return NULL;
  }

  char *token_end = token_start + 1;
  while (
    stringContainsChar(NOT_ZERO_DIGITS, *token_end) ||
    stringContainsChar(ZERO_DIGIT, *token_end)
  ) ++token_end;
  return chopFloatTail(token_end);
}
