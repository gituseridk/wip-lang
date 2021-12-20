#include <stdlib.h>
#include <stdio.h>

#include "utils/array/array.h"
#include "syntax-tree/handlers/expression/parser.h"
#include "syntax-tree/syntax-helpers.h"

#include "./parser.h"

List* parseParentheses(List *start_token, SyntaxNode *result, char **error) {
  *error = NULL;

  TokenData *token_data = (TokenData*) listGetValue(start_token);

  if (token_data->token.id != TOKEN_BRACKET_OPEN || *(token_data->value) != '(') {
    *error = "Unexpected token, expect open parentheses";
    return start_token;
  }

  List *current_token = trimTokensLeft(listNext(start_token));

  current_token = parseExpression(current_token, result, error, NULL);

  if (*error != NULL) {
    return current_token;
  }

  current_token = trimTokensLeft(current_token);

  token_data = (TokenData*) listGetValue(current_token);
  if (token_data->token.id != TOKEN_BRACKET_CLOSE || *(token_data->value) != ')') {
    *error = "Unexpected token, expect close parentheses";
    return current_token;
  }

  return listNext(current_token);
}
