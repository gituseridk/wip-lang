#include <stdio.h>
#include "token/token-data.h"

void printToken(void *self, const void *_token, int index, const Array *tokens) {
  TokenData *token = (TokenData*)_token;
  printf(
    "tokens[%d]: { name: '%s', value: '%s', row: %d, col: %d }\n",
    index,
    token->token.name,
    token->value,
    token->row,
    token->col
  );
}

int main() {
  char *src =
    "kek = 100+20130001 - 124f + 123.00423f + 0.0 +  .0124 + .9235  ;     \n"
    " \t lol=kek + 10.0;\n";
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
