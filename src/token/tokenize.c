#include <stdio.h>
#include <stdlib.h>

#include "utils/string/string.h"
#include "utils/logger/log-src-error.h"

#include "./token-data.h"
#include "./tokens.h"

typedef struct {
  char *token_start;
  char* result_token_end;
} HandlerProps;

static bool findTokenHandler(void *_self, void *_token, int index, const Array *array) {
  Token token = *(Token*) _token;
  HandlerProps *self = (HandlerProps*) _self;
  char *token_end = token.chopToken(self->token_start);
  if (token_end == NULL) {
    return false;
  }
  self->result_token_end = token_end;
  return true;
}

Array* tokenize(char *src) {
  Array *result = createEmptyArray(1, sizeof(TokenData));

  char *token_start = src;

  int start_col = 1;
  int start_row = 1;

  int col = 1;
  int row = 1;

  while (*token_start != '\0') {
    HandlerProps props = (HandlerProps) {
      .token_start = token_start,
    };
    Token *token = arrayFind(getTokens(), findTokenHandler, &props);

    if (token == NULL) {
      printSourceError(src, "Unknow token", row, col);
      arrayFree(result);
      return NULL;
    }
    char *token_end = props.result_token_end;
    int size = token_end - token_start;

    char *token_value = stringGetSubstring(token_start, 0, size - 1);
    TokenData token_data = (TokenData) {
      .token = *token,
      .size = size,
      .value = token_value,
      .row = row,
      .col = col,
    };
    arrayPush(result, &token_data);

    for (char *i = token_start; i != token_end; ++i) {
      ++col;
      if (*i == '\n') {
        col = 1;
        ++row;
      }
    }
    token_start = token_end;
  }

  return result;
}
