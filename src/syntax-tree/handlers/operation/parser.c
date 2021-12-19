#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

#include "utils/array/array.h"
#include "syntax-tree/handlers/expression/parser.h"
#include "syntax-tree/handlers/initialization/parser.h"
#include "syntax-tree/handlers/literal/parser.h"
#include "syntax-tree/syntax-helpers.h"
#include "./parser.h"
#include "./data.h"

static int getOperationId(char *operation) {
  if (strcmp(operation, "+") == 0) {
    return OPERATION_ID_SUM;
  }
  if (strcmp(operation, "-") == 0) {
    return OPERATION_ID_DIFFERENCE;
  }
  if (strcmp(operation, "/") == 0) {
    return OPERATION_ID_RATIO;
  }
  if (strcmp(operation, "*") == 0) {
    return OPERATION_ID_PRODUCT;
  }
  return -1;
}

List *parseOperation(List *tokens, SyntaxNode *result, char **error) {
  *error = NULL;
  *result = (SyntaxNode) {
    .data = NULL,
    .handler = getSyntaxNodeHandler(SYNTAX_OPERATION),
  };

  List *current_token = trimTokensLeft(tokens);
  if (current_token == NULL) {
    *error = "Failed to parse operation, end of scope";
    return current_token;
  }

  SyntaxNode left_syntax_node;
  current_token = parseExpression(current_token, &left_syntax_node, error, true);
  if (*error != NULL) {
    return current_token;
  }

  current_token = trimTokensLeft(current_token);
  if (current_token == NULL) {
    *error = "Failed to parse operation, end of scope";
    return current_token;
  }

  TokenData *middle_token = (TokenData*) listGetValue(current_token);

  if (middle_token->token.id != TOKEN_OPERATOR_OPERATIONS) {
    *error = "Failed to parse operation, unexpexted operation token";
    return current_token;
  }

  int operation_id = getOperationId(middle_token->value);
  if (operation_id == -1) {
    *error = "Failed to parse operation, unknown operation";
    return current_token;
  }

  current_token = trimTokensLeft(listNext(current_token));
  if (current_token == NULL) {
    *error = "Failed to parse operation, end of scope";
    return current_token;
  }
  
  SyntaxNode right_syntax_node;
  current_token = parseExpression(current_token, &right_syntax_node, error, false);
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
