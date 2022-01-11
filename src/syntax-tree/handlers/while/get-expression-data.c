#include <stdlib.h>

#include "utils/logger/log-src-error.h"
#include "../initialization/data.h"
#include "./data.h"

void getWhileExpressionData(
  const char *src,
  void *raw_data,
  List *token,
  ExpressionData *result,
  unsigned *offset,
  int handler_id
) {
  SyntaxWhileData *data = (SyntaxWhileData*) raw_data;
  expressionInit(result, EXPRESSION_WHILE, token);

  ExpressionData condition;
  condition.parent_scope = result->parent_scope;
  condition.result_type.type_id = TYPE_ID_VOID;
  condition.result_type.data = NULL;

  data->condition.handler->getExpressionData(
    src,
    data->condition.data,
    data->condition.token,
    &condition,
    offset,
    data->condition.handler->id
  );

  if (!isBool(&(condition.result_type))) {
    throwSourceError(src, "if condition is not convertable to boolean", data->condition.token);
  }

  ExpressionData expression;
  expression.parent_scope = result->parent_scope;
  setVoidType(&(expression.result_type));

  data->expression.handler->getExpressionData(
    src,
    data->expression.data,
    data->expression.token,
    &expression,
    offset,
    data->expression.handler->id
  );

  result->child_expressions = newArray(ExpressionData, condition, expression);
}
