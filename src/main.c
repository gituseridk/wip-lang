#include <stdio.h>
#include "token/token-data.h"

void printToken(TokenData *token, int index) {
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
    "int kek = 6.9 + 42.0;\n";
  printf("===src===\n%s\n===SRC===\n\n", src);
  List *tokens = tokenize(src);

  if (tokens == NULL) {
    printf("failed to tokenize sources\n");
    return 1;
  }

  printf("==tokens==\n");
  int i = 0;
  for (List *token = tokens; token != NULL; token = listNext(token)) {
    printToken((TokenData*) listGetValue(token), i);
    ++i;
  }
  printf("==TOKENS==\n");
  listFree(tokens);

  return 0;
}
