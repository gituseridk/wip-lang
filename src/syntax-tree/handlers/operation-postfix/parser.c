#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "utils/array/array.h"
#include "syntax-tree/handlers/expression/parser.h"
#include "syntax-tree/handlers/initialization/parser.h"
#include "syntax-tree/handlers/literal/parser.h"
#include "syntax-tree/syntax-helpers.h"
#include "./parser.h"
#include "./data.h"

static int getOperationId(int token_id) {
  if (token_id == TOKEN_OPERATOR_INC) {
    return OPERATION_POSTFIX_ID_INC;
  }
  if (token_id == TOKEN_OPERATOR_DEC) {
    return OPERATION_POSTFIX_ID_DEC;
  }

  return -1;
}

List *parseOperationPostfix(List *tokens, SyntaxNode *left, SyntaxNode *result, char **error) {
  *error = NULL;
  *result = (SyntaxNode) {
    .data = NULL,
    .handler = getSyntaxNodeHandler(SYNTAX_OPERATION_POSTFIX),
  };

  List *current_token = trimTokensLeft(tokens);
  result->token = current_token;

  if (current_token == NULL) {
    *error = "Failed to parse operation, end of scope";
    return current_token;
  }

  TokenData *operator_token = (TokenData*) listGetValue(current_token);

  int operation_id = getOperationId(operator_token->token.id);
  if (operation_id == -1) {
    *error = "Failed to parse postfix operator, unexpected token";
    return current_token;
  }

  SyntaxOperationPostfixData *data = malloc(sizeof(SyntaxOperationPostfixData));
  data->expression = *left;
  data->operation_id = operation_id;
  result->data = data;

  return listNext(current_token);
}
