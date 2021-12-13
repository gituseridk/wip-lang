#include <stdio.h>
#include "token/token-data.h"

void printToken(void *self, const void *_token, int index, const Array *tokens) {
  TokenData *token = (TokenData*)_token;
  printf("tokens[%d]: { name: '%s', value: '%s' }\n", index, token->token.name, token->value);
}

int main() {
  char *src =
    "kek = 1+2   ;     \n"
    " \t lol=kek + 10.0;\n"
    "str=;";
  printf("===src===\n%s\n===SRC===\n\n", src);
  Array *tokens = tokenize(src);

  if (tokens == NULL) {
    printf("failed to tokenize sources\n");
    return 0;
  }

  printf("==tokens==\n");
  arrayForEach(tokens, printToken, NULL);
  printf("==TOKENS==\n");

  return 0;
}
