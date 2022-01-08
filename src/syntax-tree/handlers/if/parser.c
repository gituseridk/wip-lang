#include <stdlib.h>
#include <stdio.h>

#include "syntax-tree/handlers/expression/parser.h"
#include "syntax-tree/handlers/scope/parser.h"
#include "syntax-tree/syntax-helpers.h"
#include "./parser.h"
#include "./data.h"

List *parseIf(List *tokens, SyntaxNode *result, char **error) {
  *error = NULL;
  *result = (SyntaxNode) {
    .data = NULL,
    .handler = getSyntaxNodeHandler(SYNTAX_IF),
  };

  List *current_token = trimTokensLeft(tokens);
  result->token = current_token;

  current_token = chopToken(current_token, TOKEN_KEYWORD, "if", error);

  if (*error != NULL) {
    return current_token;
  }

  SyntaxIfData *data = malloc(sizeof(SyntaxIfData));

  current_token = trimTokensLeft(current_token);
  current_token = parseExpression(current_token, &(data->condition), error);
  if (*error != NULL) {
    free(data);
    return current_token;
  }

  current_token = trimTokensLeft(current_token);
  current_token = parseScope(current_token, &(data->expression), error);
  if (*error != NULL) {
    free(data);
    return current_token;
  }

  result->data = data;

  return current_token;
}
