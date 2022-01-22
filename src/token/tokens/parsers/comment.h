ChopToken(comment, token, error) {
  if (token[0] == '/' && token[1] == '/') {
    token += 2;

    while (*token != '\n' && *token != '\0') ++token;

    return token;
  }
  return NULL;
}
