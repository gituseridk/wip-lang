
ChopToken(separator, token_start, error) {
  if (!stringContainsChar(SEPARATORS, *token_start)) {
    return NULL;
  }
  return token_start + 1;
}
