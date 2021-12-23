#include <stdio.h>
#include <stdlib.h>

#include "utils/array/array.h"
#include "utils/string/string.h"
#include "utils/logger/log-src-error.h"

#include "./token-data.h"
#include "./tokens.h"

typedef struct {
  char *token_start;
  char* result_token_end;
} HandlerProps;

typedef struct {
  char *error;
  char *token_end;
  Token token;
} TokenChopResult;

static void findTokenHandler(void *_self, void *_result, void *_token, int index, const Array *array) {
  Token token = *(Token*) _token;
  TokenChopResult *result = (TokenChopResult*) _result;
  result->error = NULL;
  result->token_end = NULL;
  result->token = token;

  char *token_start = (char*) _self;
  char* tokenization_error = NULL;
  char *token_end = token.chopToken(token_start, &tokenization_error);
  if (token_end == NULL) {
    result->error = tokenization_error;
    return;
  }
  result->token_end = token_end;
  return;
}

static bool hasError(void *self, void *_chop_result, int index, const Array *array) {
  TokenChopResult *chop_result = (TokenChopResult*) _chop_result;
  return chop_result->error != NULL;
}

static bool hasResult(void *self, void *_chop_result, int index, const Array *array) {
  TokenChopResult *chop_result = (TokenChopResult*) _chop_result;
  return chop_result->token_end != NULL;
}

List* tokenize(char *src) {
  List *result = NULL;
  List *last_token_result = NULL;

  char *token_start = src;

  int col = 1;
  int row = 1;

  while (*token_start != '\0') {
    Array *token_chop_results = arrayMap(getTokens(), sizeof(TokenChopResult), findTokenHandler, token_start);

    TokenChopResult *token_result = (TokenChopResult*) arrayFind(token_chop_results, hasResult, NULL);

    if (token_result == NULL) {
      TokenChopResult *error_result = (TokenChopResult*) arrayFind(token_chop_results, hasError, NULL);
      if (error_result != NULL) {
        printSourceError(src, error_result->error, row, col);
      } else {
        printSourceError(src, "Unknow token", row, col);
      }
      arrayFree(token_chop_results);
      return NULL;
    }

    Token token = token_result->token;
    char *token_end = token_result->token_end;
    int size = token_end - token_start;

    char *token_value = stringGetSubstring(token_start, 0, size - 1);
    TokenData token_data = (TokenData) {
      .token = token,
      .size = size,
      .value = token_value,
      .row = row,
      .col = col,
    };
    last_token_result = listPushAfter(last_token_result, &token_data, sizeof(TokenData));
    if (result == NULL) {
      result = last_token_result;
    }

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
