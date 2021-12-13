ChopToken(literal_int, token_start) {
  if (stringContainsChar(ZERO_DIGIT, token_start[0])) {
    if (stringContainsChar(ZERO_DIGIT, token_start[1]) || stringContainsChar(NOT_ZERO_DIGITS, token_start[1])) {
      return NULL;
    }
    return token_start + 1;
  }

  if (!stringContainsChar(NOT_ZERO_DIGITS, *token_start)) {
    return NULL;
  }

  char *token_end = token_start + 1;
  while (
    stringContainsChar(NOT_ZERO_DIGITS, *token_end) ||
    stringContainsChar(ZERO_DIGIT, *token_end)
  ) ++token_end;

  return token_end;
}
