
ChopToken(identifier, token_start, error) {
  if (
    !stringContainsChar(UPPER_CASE_LETTERS, *token_start) &&
    !stringContainsChar(LOWER_CASE_LETTERS, *token_start) &&
    *token_start != '_'
  ) {
    return NULL;
  }

  char *token_end = token_start + 1;
  while (*token_end == '_' || checkIfLetterOrDigit(*token_end)) ++token_end;

  return token_end;
}
