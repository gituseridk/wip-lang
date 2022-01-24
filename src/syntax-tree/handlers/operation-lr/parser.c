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

static int getOperationPriority(int operation_id) {
  switch (operation_id)
  {
  case OPERATION_ID_AND:
  case OPERATION_ID_OR:
    return 0;

  case OPERATION_ID_EQUALS:
  case OPERATION_ID_NOT_EQUALS:
  case OPERATION_ID_EQUALS_STRICT:
  case OPERATION_ID_NOT_EQUALS_STRICT:
  case OPERATION_ID_GRATER_OR_EQUAL:
  case OPERATION_ID_LESS_OR_EQUAL:
  case OPERATION_ID_GRATER:
  case OPERATION_ID_LESS:
    return 1;

  case OPERATION_ID_SUM:
  case OPERATION_ID_DIFFERENCE:
    return 2;

  case OPERATION_ID_RATIO:
  case OPERATION_ID_PRODUCT:
    return 3;

  case OPERATION_ID_BIT_OR:
  case OPERATION_ID_BIT_AND:
    return 4;
  
  default:
    return 5;
  }
}

static int getOperationId(int token_id) {
  switch (token_id)
  {
  case TOKEN_OPERATOR_SUM:
    return OPERATION_ID_SUM;

  case TOKEN_OPERATOR_DIFFERENCE:
    return OPERATION_ID_DIFFERENCE;
  
  case TOKEN_OPERATOR_RATIO:
    return OPERATION_ID_RATIO;
  
  case TOKEN_OPERATOR_PRODUCT:
    return OPERATION_ID_PRODUCT;
  
  case TOKEN_OPERATOR_BIT_OR:
    return OPERATION_ID_BIT_OR;
  
  case TOKEN_OPERATOR_AND:
    return OPERATION_ID_AND;
  
  case TOKEN_OPERATOR_OR:
    return OPERATION_ID_OR;
  
  case TOKEN_OPERATOR_EQUALS:
    return OPERATION_ID_EQUALS;
  
  case TOKEN_OPERATOR_EQUALS_STRICT:
    return OPERATION_ID_EQUALS_STRICT;
  
  case TOKEN_OPERATOR_NOT_EQUALS:
    return OPERATION_ID_NOT_EQUALS;
  
  case TOKEN_OPERATOR_NOT_EQUALS_STRICT:
    return OPERATION_ID_NOT_EQUALS_STRICT;

  case TOKEN_OPERATOR_GRATER_OR_EQUAL:
    return OPERATION_ID_GRATER_OR_EQUAL;
  
  case TOKEN_OPERATOR_LESS_OR_EQUAL:
    return OPERATION_ID_LESS_OR_EQUAL;
  
  case TOKEN_OPERATOR_GRATER:
    return OPERATION_ID_GRATER;
  
  case TOKEN_OPERATOR_LESS:
    return OPERATION_ID_LESS;
  
  default:
    return -1;
  }

}

List *parseOperation(List *tokens, SyntaxNode *left, SyntaxNode *result, char **error) {
  *error = NULL;
  *result = (SyntaxNode) {
    .data = NULL,
    .handler = getSyntaxNodeHandler(SYNTAX_OPERATION_LR),
    .priority = SYNTAX_OPERATION_LR * SYNTAX_PRIORITY_OFFSET,
  };

  List *current_token = trimTokensLeft(tokens);
  result->token = current_token;

  if (current_token == NULL) {
    *error = "Failed to parse operation, end of scope";
    return current_token;
  }

  TokenData *operation_token = (TokenData*) listGetValue(current_token);

  int operation_id = getOperationId(operation_token->token.id);
  if (operation_id == -1) {
    *error = "Failed to parse operation, unexpected token";
    return current_token;
  }

  result->priority += getOperationPriority(operation_id);

  current_token = trimTokensLeft(listNext(current_token));
  if (current_token == NULL) {
    *error = "Failed to parse operation, end of scope";
    return current_token;
  }
  
  SyntaxNode right_syntax_node;
  current_token = parseExpression(current_token, &right_syntax_node, error, false, result->priority);
  if (*error != NULL) {
    return current_token;
  }

  SyntaxOperationData *data = malloc(sizeof(SyntaxOperationData));
  data->left = *left;
  data->right = right_syntax_node;
  data->operation_id = operation_id;
  result->data = data;

  return current_token;
}
