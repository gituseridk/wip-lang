#include <stdlib.h>

#include "utils/logger/log-src-error.h"
#include "./data.h"

void getOperationLRExpressionData(
  const char *src,
  void *raw_data,
  List *token,
  ExpressionData *result,
  int *offset,
  int handler_id
) {
  SyntaxOperationData *data = (SyntaxOperationData*) raw_data;
  expressionInit(result, EXPRESSION_OPERATIONS + data->operation_id, "operation_lr", token, false);
  result->compileX86 = compileOperationLRX86;

  ExpressionData left;
  left.parent_scope = result->parent_scope;
  setVoidType(&(left.result_type));

  ExpressionData right;
  right.parent_scope = result->parent_scope;
  setVoidType(&(right.result_type));

  data->left.handler->getExpressionData(
    src,
    data->left.data,
    data->left.token,
    &left,
    offset,
    data->left.handler->id
  );
  
  if (left.result_type.type_id == TYPE_ID_VOID) {
    throwSourceError(src, "left side expression is void type", token);
  }

  data->right.handler->getExpressionData(
    src,
    data->right.data,
    data->right.token,
    &right,
    offset,
    data->left.handler->id
  );

  if (!isTypesCompatible(&(left.result_type), &(right.result_type))) {
    throwSourceError(src, "right side and left side expressions are of different types", token);
  }

  result->result_type = left.result_type;
  result->child_expressions = newArray(ExpressionData, left, right);
}

