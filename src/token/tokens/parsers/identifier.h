
ChopToken(identifier, token_start, error) {
  if (!stringContainsChar(UPPER_CASE_LETTERS, *token_start) && !stringContainsChar(LOWER_CASE_LETTERS, *token_start)) {
    return NULL;
  }

  char *token_end = token_start + 1;
  while (checkIfLetterOrDigit(*token_end)) ++token_end;

  return token_end;
}
