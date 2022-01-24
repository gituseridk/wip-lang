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
    .priority = SYNTAX_IF * SYNTAX_PRIORITY_OFFSET,
  };

  List *current_token = trimTokensLeft(tokens);
  result->token = current_token;

  current_token = chopToken(current_token, TOKEN_KEYWORD, "if", error);

  if (*error != NULL) {
    return current_token;
  }

  SyntaxIfData *data = malloc(sizeof(SyntaxIfData));
  data->else_expression = NULL;

  current_token = trimTokensLeft(current_token);
  current_token = parseExpression(current_token, &(data->condition), error, false, 0);
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

  current_token = trimTokensLeft(current_token);
  current_token = chopToken(current_token, TOKEN_KEYWORD, "else", error);
  if (*error != NULL) {
    *error = NULL;
    return current_token;
  }

  // patse "else" block
  data->else_expression = malloc(sizeof(SyntaxNode));

  current_token = parseExpression(current_token, data->else_expression, error, true, 0);
  if (*error != NULL) {
    free(data);
    return current_token;
  }
  int else_expr_id = data->else_expression->handler->id;

  if (
    else_expr_id != SYNTAX_IF &&
    else_expr_id != SYNTAX_SCOPE
  ) {
    *error = "failed to parse else expression, expected \"scope\" or \"if\"";
    free(data);
  }

  return current_token;
}
