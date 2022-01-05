#include <stdlib.h>

#include "utils/logger/log-src-error.h"
#include "./data.h"

void getOperationLRExpressionData(
  const char *src,
  void *raw_data,
  List *token,
  ExpressionData *result
) {
  SyntaxOperationData *data = (SyntaxOperationData*) raw_data;
  result->id = EXPRESSION_OPERATIONS + data->operation_id;

  ExpressionData left;
  left.parent_scope = result->parent_scope;
  left.result_type.type_id = SYNTAX_TYPE_ID_VOID;

  ExpressionData right;
  right.parent_scope = result->parent_scope;
  right.result_type.type_id = SYNTAX_TYPE_ID_VOID;

  data->left.handler->getExpressionData(
    src,
    data->left.data,
    data->left.token,
    &left
  );

  data->right.handler->getExpressionData(
    src,
    data->right.data,
    data->right.token,
    &right
  );

  if (left.result_type.type_id != right.result_type.type_id || left.result_type.data != right.result_type.data) {
    TokenData *token_data = (TokenData*) listGetValue(token);
    printSourceError(src, "right side and left side are of different types", token_data->row, token_data->col);
    exit(0);
  }

  result->child_expressions = newArray(ExpressionData, left, right);
}

