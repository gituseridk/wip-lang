
ChopToken(separator, token_start) {
  if (!stringContainsChar(SEPARATORS, *token_start)) {
    return NULL;
  }
  return token_start + 1;
}
