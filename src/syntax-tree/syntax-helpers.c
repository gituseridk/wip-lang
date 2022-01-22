#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


#include "token/token-data.h"
#include "./syntax-helpers.h"

List *chopToken(List *start_token, int token_id, const char *token_value, char **error) {
  *error = NULL;
  TokenData *token = (TokenData*) listGetValue(start_token);
  if (token_value == NULL) {
    if (token->token.id != token_id) {
      asprintf(error, "Unexpected token with id = %d, expect id = %d", token->token.id, token_id);
      return start_token;
    }
  } else if (token->token.id != token_id || strcmp(token->value, token_value) != 0) {
    asprintf(error, "Unexpected token, expect '%s'", token_value);
    return start_token;
  }
  return listNext(start_token);
}

static bool isWhiteSpaceToken(List *token) {
  TokenData *token_data = (TokenData*)listGetValue(token);
  int id = token_data->token.id;
  return id == TOKEN_WHITE_SPACE || id == TOKEN_COMMENT;
}

List *trimTokensLeft(List *start_token) {
  while (start_token != NULL && isWhiteSpaceToken(start_token)) {
    start_token = listNext(start_token);
  }
  return start_token;
}

List *chopExpressionEnd(List *start_token, char **error) {
  *error = NULL;

  List *token = trimTokensLeft(start_token);
  if (token == NULL) {
    return NULL;
  }
  TokenData *token_data = (TokenData*) listGetValue(token);
  if (token_data->token.id != TOKEN_SEPARATOR_EXPRESSION) {
    *error = "Unexpected token, ';' expected";
    return token;
  }

  return listNext(token);
}

static bool isTrmableHard(TokenData *token) {
  return token != NULL && (
    token->token.id == TOKEN_WHITE_SPACE ||
    token->token.id == TOKEN_COMMENT ||
    token->token.id == TOKEN_SEPARATOR_EXPRESSION
  );
}

List *trimTokensLeftHard(List *start_token) {
  while (start_token != NULL && isTrmableHard(listGetValue(start_token))) {
    start_token = listNext(start_token);
  }
  return start_token;
}
