#include <stdlib.h>
#include <stdio.h>

#include "type-definition/pointer/data.h"
#include "utils/logger/log-src-error.h"
#include "./data.h"

void getOperationPrefixExpressionData(
  const char *src,
  void *raw_data,
  List *token,
  ExpressionData *result,
  int *offset,
  int handler_id
) {
  SyntaxOperationPrefixData *data = (SyntaxOperationPrefixData*) raw_data;
  expressionInit(result, EXPRESSION_OPERATIONS_PREFIX + data->operation_id, "operation_prefix", token, false);
  result->compileX86 = compileOperationPrefixX86;

  ExpressionData expression;
  expression.parent_scope = result->parent_scope;
  expression.result_type.type_id = TYPE_ID_VOID;
  expression.result_type.data = NULL;

  data->expression.handler->getExpressionData(
    src,
    data->expression.data,
    data->expression.token,
    &expression,
    offset,
    data->expression.handler->id
  );

  if (data->operation_id == OPERATION_PREFIX_ID_DEREFERENCING) {
    if (expression.result_type.type_id == TYPE_ID_POINTER) {
      TypePointerData *pointer_data = (TypePointerData*) expression.result_type.data;
      result->result_type = pointer_data->type;
      result->child_expressions = newArray(ExpressionData, expression);
      return;
    }
    char err[100];
    sprintf(err, "cannot dereference %s type", getTypeName(&(expression.result_type)));
    throwSourceError(src, err, token);
  }

  // !TODO add expression overload
  if (expression.result_type.type_id != TYPE_ID_INT) {
    throwSourceError(src, "wrong expression type, expected int", token);
  }

  result->result_type = expression.result_type;
  result->child_expressions = newArray(ExpressionData, expression);
}

