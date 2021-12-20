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

  if (*token_end == 'f') {
    return token_end + 1;
  }

  return token_end;
}

// !TODO parse exponential floats

ChopToken(literal_float, token_start, error) {
  char *token_end = token_start;

  if (stringContainsChar(ZERO_DIGIT, *token_end)) {
    return chopFloatTail(token_end + 1);
  }

  if (*token_end == '.') {
    return chopFloatTail(token_end);
  }

  if (!stringContainsChar(NOT_ZERO_DIGITS, *token_end)) {
    return NULL;
  }

  ++token_end;

  while (
    stringContainsChar(NOT_ZERO_DIGITS, *token_end) ||
    stringContainsChar(ZERO_DIGIT, *token_end)
  ) ++token_end;
  return chopFloatTail(token_end);
}
