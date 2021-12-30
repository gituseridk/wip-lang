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
  if (token_id == TOKEN_OPERATOR_SUM) {
    return OPERATION_ID_SUM;
  }
  if (token_id == TOKEN_OPERATOR_DIFFERENCE) {
    return OPERATION_ID_DIFFERENCE;
  }
  if (token_id == TOKEN_OPERATOR_RATIO) {
    return OPERATION_ID_RATIO;
  }
  if (token_id == TOKEN_OPERATOR_PRODUCT) {
    return OPERATION_ID_PRODUCT;
  }
  if (token_id == TOKEN_OPERATOR_POWER) {
    return OPERATION_ID_POWER;
  }
  if (token_id == TOKEN_OPERATOR_BIT_OR) {
    return OPERATION_ID_BIT_OR;
  }
  if (token_id == TOKEN_OPERATOR_AND) {
    return OPERATION_ID_AND;
  }
  if (token_id == TOKEN_OPERATOR_OR) {
    return OPERATION_ID_OR;
  }
  if (token_id == TOKEN_OPERATOR_EQUALS) {
    return OPERATION_ID_EQUALS;
  }
  if (token_id == TOKEN_OPERATOR_EQUALS_STRICT) {
    return OPERATION_ID_EQUALS_STRICT;
  }
  if (token_id == TOKEN_OPERATOR_NOT_EQUALS) {
    return OPERATION_ID_NOT_EQUALS;
  }
  if (token_id == TOKEN_OPERATOR_NOT_EQUALS_STRICT) {
    return OPERATION_ID_NOT_EQUALS_STRICT;
  }

  if (token_id == TOKEN_OPERATOR_GRATER_OR_EQUAL) {
    return OPERATION_ID_GRATER_OR_EQUAL;
  }
  if (token_id == TOKEN_OPERATOR_LESS_OR_EQUAL) {
    return OPERATION_ID_LESS_OR_EQUAL;
  }
  if (token_id == TOKEN_OPERATOR_GRATER) {
    return OPERATION_ID_GRATER;
  }
  if (token_id == TOKEN_OPERATOR_LESS) {
    return OPERATION_ID_LESS;
  }

  return -1;
}

List *parseOperation(List *tokens, SyntaxNode *result, char **error) {
  *error = NULL;
  *result = (SyntaxNode) {
    .data = NULL,
    .handler = getSyntaxNodeHandler(SYNTAX_OPERATION_LR),
  };

  List *current_token = trimTokensLeft(tokens);
  if (current_token == NULL) {
    *error = "Failed to parse operation, end of scope";
    return current_token;
  }

  SyntaxNode left_syntax_node;
  current_token = parseExpression(current_token, &left_syntax_node, error, parseOperation);
  if (*error != NULL) {
    return current_token;
  }

  current_token = trimTokensLeft(current_token);
  if (current_token == NULL) {
    *error = "Failed to parse operation, end of scope";
    return current_token;
  }

  TokenData *middle_token = (TokenData*) listGetValue(current_token);

  int operation_id = getOperationId(middle_token->token.id);
  if (operation_id == -1) {
    *error = "Failed to parse operation, unexpected token";
    return current_token;
  }

  current_token = trimTokensLeft(listNext(current_token));
  if (current_token == NULL) {
    *error = "Failed to parse operation, end of scope";
    return current_token;
  }
  
  SyntaxNode right_syntax_node;
  current_token = parseExpression(current_token, &right_syntax_node, error, NULL);
  if (*error != NULL) {
    return current_token;
  }

  SyntaxOperationData *data = malloc(sizeof(SyntaxOperationData));
  data->left = left_syntax_node;
  data->right = right_syntax_node;
  data->operation_id = operation_id;
  result->data = data;

  return current_token;
}
