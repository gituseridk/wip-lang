ChopToken(separator_expression, token_start, error) {
  if (!stringContainsChar(SEPARATORS_EXPRESSION, *token_start)) {
    return NULL;
  }
  return token_start + 1;
}
