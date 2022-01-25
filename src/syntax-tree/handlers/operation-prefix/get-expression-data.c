#include <stdlib.h>
#include <stdio.h>

#include "type-definition/pointer/data.h"
#include "utils/logger/log-src-error.h"
#include "./data.h"

void getOperationPrefixExpressionData(
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
  setVoidType(&(expression.result_type));

  data->expression.handler->getExpressionData(
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
    throwSourceError(err, token);
  }

  if (data->operation_id == OPERATION_PREFIX_ID_NEGOTATION) {
    setVoidType(&(result->result_type));
    // !TODO return boolean
    result->result_type.type_id = TYPE_ID_INT;

    result->child_expressions = newArray(ExpressionData, expression);
    return;
  }

  if (
    expression.result_type.type_id != TYPE_ID_INT &&
    expression.result_type.type_id != TYPE_ID_POINTER
  ) {
    char err[100];
    sprintf(err, "prefix operarion for type \"$%s\" is not supported yet", getTypeName(&(expression.result_type)));
    throwSourceError(err, token);
  }

  result->result_type = expression.result_type;
  result->child_expressions = newArray(ExpressionData, expression);
}

