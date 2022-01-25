#include <stdlib.h>

#include "utils/logger/log-src-error.h"
#include "../initialization/data.h"
#include "./data.h"

void getAssignationExpressionData(
  void *raw_data,
  List *token,
  ExpressionData *result,
  int *offset,
  int handler_id
) {
  SyntaxAssignationData *data = (SyntaxAssignationData*) raw_data;
  expressionInit(result, EXPRESSION_ASSIGNATION, "assignation", token, false);
  result->compileX86 = compileAssignationX86;

  ExpressionData left;
  left.parent_scope = result->parent_scope;
  ExpressionData right;
  right.parent_scope = result->parent_scope;

  data->right.handler->getExpressionData(
    data->right.data,
    data->right.token,
    &right,
    offset,
    data->right.handler->id
  );
  result->result_type = right.result_type;

  if (right.result_type.type_id == TYPE_ID_VOID) {
    throwSourceError("unexpected right side expression with void type", data->right.token);
  }

  if (data->left.handler->getExpressionData == getInitializationExpressionData) {
    SyntaxInitializationData *left_data = (SyntaxInitializationData*) data->left.data;
    if (left_data->type == NULL) {
      left.result_type = right.result_type;
    } else {
      left.result_type = *(left_data->type);
    }
  }

  data->left.handler->getExpressionData(
    data->left.data,
    data->left.token,
    &left,
    offset,
    data->left.handler->id
  );

  if (left.result_type.is_constant && left.id != EXPRESSION_INITIALIZATION) {
    throwSourceError("left expression is constant", data->left.token);
  }

  if (!isTypesCompatible(&(left.result_type), &(right.result_type))) {
    throwSourceError("type mismatch", data->left.token);
  }

  result->child_expressions = newArray(ExpressionData, left, right);
}
