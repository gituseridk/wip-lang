#include <stdio.h>
#include <stdlib.h>
#include "utils/string/string.h"
#include "./token-data.h"
#include "./tokens.h"

typedef struct {
  const char *token_str;
  int size;
} TokenCheckProps;

static bool checkTocken(void *_self, const void *_token, int index, const Array *array) {
  TokenCheckProps *self = (TokenCheckProps*) _self;
  Token *token = (Token*)_token;
  return token->testString(self->token_str, self->size);
}

Array* tokenize(char *src) {
  Array *result = createEmptyArray(1, sizeof(TokenData));

  int iterations_limit = 100;

  char *token_start = src;
  char *token_end = src;

  int start_col = 1;
  int start_row = 1;

  int col = 0;
  int row = 1;

  Token *last_token = NULL;
  while (*token_end != '\0') {
    if (--iterations_limit == 0) {
      break;
    }

    ++col;
    if (*token_end == '\n') {
      ++row;
      col = 0;
    }
    int token_size = token_end - token_start + 1;
    char *token_str = stringGetSubstring(token_start, 0, token_size - 1);
    printf("%d token: '%s'\n", iterations_limit, token_str);

    TokenCheckProps props = (TokenCheckProps) {
      .token_str = token_str,
      .size = token_size,
    };
    Token *token = (Token*) arrayFind(getTokens(), checkTocken, &props);

    if (token == NULL) {
      if (last_token == NULL) {
        printf("unexpected token '%*.*s' at %d:%d\n", token_size, token_size, token_start, row, col);
        arrayFree(result);
        free(token_str);
        return NULL;
      }

      TokenData data = (TokenData) {
        .id = last_token->id,
        .value = token_str,
        .col = start_col,
        .row = start_row,
        .size = token_size,
      };
      token_start = token_end;
      arrayPush(result, &data);
      free(token_str);
      last_token = token;
      continue;
    }

    last_token = token;
    free(token_str);
    ++token_end;
  }

  return result;
}
