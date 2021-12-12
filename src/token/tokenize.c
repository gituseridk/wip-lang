#include <stdio.h>
#include "./token-data.h"
#include "./tokens.h"

static void checkTocken(const void *_token, int index, const Array *self) {
  Token *token = (Token*)_token;
  printf("token %d\n", token->id);
}

Array* tokenize(char *src) {
  Array *result = createEmptyArray(1, sizeof(Token));

  char *token_start = src;
  char *token_end = src;
  while (*token_end != '\0') {
    int token_size = token_end - token_start + 1;
    printf("check if '%*.*s' is token\n", token_size, token_size, token_start);
    arrayForEach(getTokens(), checkTocken);
    ++token_end;
  }

  return result;
}
