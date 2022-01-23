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
    return OPERATION_PREFIX_ID_INC;
  }
  if (token_id == TOKEN_OPERATOR_DEC) {
    return OPERATION_PREFIX_ID_DEC;
  }
  if (token_id == TOKEN_OPERATOR_PRODUCT) {
    return OPERATION_PREFIX_ID_DEREFERENCING;
  }
  if (token_id == TOKEN_OPERATOR_NOT) {
    return OPERATION_PREFIX_ID_NEGOTATION;
  }

  return -1;
}

List *parseOperationPrefix(List *tokens, SyntaxNode *result, char **error) {
  *error = NULL;
  *result = (SyntaxNode) {
    .data = NULL,
    .handler = getSyntaxNodeHandler(SYNTAX_OPERATION_PREFIX),
    .priority = SYNTAX_OPERATION_PREFIX * SYNTAX_PRIORITY_OFFSET,
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
    *error = "Failed to parse prefix operator, unexpected token";
    return current_token;
  }

  current_token = trimTokensLeft(listNext(current_token));
  if (current_token == NULL) {
    *error = "Failed to parse operation, end of scope";
    return current_token;
  }
  
  SyntaxNode expression_syntax_node;
  current_token = parseExpression(current_token, &expression_syntax_node, error, false, result->priority);
  if (*error != NULL) {
    return current_token;
  }

  SyntaxOperationPrefixData *data = malloc(sizeof(SyntaxOperationPrefixData));
  data->expression = expression_syntax_node;
  data->operation_id = operation_id;
  result->data = data;

  return current_token;
}
