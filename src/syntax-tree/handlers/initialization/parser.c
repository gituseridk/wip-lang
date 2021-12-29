#include <stdlib.h>
#include <strings.h>
#include <stdio.h>

#include "utils/array/array.h"
#include "syntax-tree/syntax-helpers.h"
#include "syntax-tree/handlers/expression/parser.h"

#include "./parser.h"
#include "./data.h"

List *parseInitialization(List *token, SyntaxNode *result, char **error) {
  *error = NULL;
  *result = (SyntaxNode) {
    .data = NULL,
    .handler = getSyntaxNodeHandler(SYNTAX_INITIALIZATION), 
  };

  TokenData *initialization_type = (TokenData*) listGetValue(token);
  if (
    initialization_type->token.id != TOKEN_KEYWORD ||
    (strcmp(initialization_type->value, "const") != 0 && strcmp(initialization_type->value, "var") != 0)
  ) {
    *error = "Unexpected token, must be a 'const' or 'var' keyword";
    return token;
  }

  token = trimTokensLeft(listNext(token));
  if (token == NULL) {
    *error = "Failed to parse initialization, end of scope";
    return token;
  }
  TokenData *name_token = (TokenData*) listGetValue(token);

  if (name_token->token.id != TOKEN_IDENTIFIER) {
    *error = "Unexpected token, must be an identifier";
    return token;
  }

  SyntaxInitializationData *data = malloc(sizeof(SyntaxInitializationData));
  data->identifier = name_token->value;
  data->is_constant = strcmp(initialization_type->value, "const") == 0;
  result->data = data;

  return listNext(token);
}
