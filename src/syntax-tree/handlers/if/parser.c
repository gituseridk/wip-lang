#include <stdlib.h>
#include <stdio.h>

#include "syntax-tree/handlers/expression/parser.h"
#include "syntax-tree/handlers/scope/parser.h"
#include "syntax-tree/syntax-helpers.h"
#include "utils/logger/log-src-error.h"

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

  List *condition_start_token = trimTokensLeft(current_token);
  current_token = parseExpression(condition_start_token, &(data->condition), error, false, 0);
  if (*error != NULL) {
    free(data);
    throwSourceError("failed to parse \"if\", expected condition", condition_start_token);
  }

  current_token = trimTokensLeft(current_token);
  current_token = parseScope(current_token, &(data->expression), error);
  if (*error != NULL) {
    free(data);
    throwSourceError("failed to parse \"if\", expected scope", current_token);
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

  List *else_start_token = trimTokensLeft(current_token);
  current_token = parseExpression(else_start_token, data->else_expression, error, true, 0);
  if (*error != NULL) {
    char err[100];
    sprintf(err, "failed to parse else expression: %s", *error);
    throwSourceError(err, else_start_token);
    return current_token;
  }
  int else_expr_id = data->else_expression->handler->id;

  if (
    else_expr_id != SYNTAX_IF &&
    else_expr_id != SYNTAX_SCOPE
  ) {
    throwSourceError("failed to parse else expression, expected \"scope\" or \"if\"", else_start_token);
  }

  return current_token;
}
