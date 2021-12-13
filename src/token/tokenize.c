#include <stdio.h>
#include <stdlib.h>
#include "utils/string/string.h"
#include "./token-data.h"
#include "./tokens.h"

static bool checkTocken(void *self, const void *_token, int index, const Array *array) {
  Token *token = (Token*)_token;
  return token->testString(self);
}

Array* tokenize(char *src) {
  Array *result = createEmptyArray(1, sizeof(Token));

  char *token_start = src;
  char *token_end = src;
  while (*token_end != '\0') {
    int token_size = token_end - token_start + 1;
    char *tokenStr = stringGetSubstring(token_start, 0, token_size);
    int tokensMatched = arrayCount(getTokens(), checkTocken, tokenStr);
    printf("for string '%*.*s' %d tokens matched\n", token_size, token_size, token_start, tokensMatched);
    free(tokenStr);
    ++token_end;
  }

  return result;
}
