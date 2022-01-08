#include <stdlib.h>

#include "utils/logger/log-src-error.h"
#include "./data.h"

void getOperationPostfixExpressionData(
  const char *src,
  void *raw_data,
  List *token,
  ExpressionData *result,
  unsigned *offset,
  int handler_id
) {
  SyntaxOperationPostfixData *data = (SyntaxOperationPostfixData*) raw_data;
  result->id = EXPRESSION_OPERATIONS_POSTFIX + data->operation_id;
  result->variables = createMap(sizeof(VariableData));

  ExpressionData expression;
  expression.parent_scope = result->parent_scope;
  expression.result_type.type_id = SYNTAX_TYPE_ID_VOID;
  expression.result_type.data = NULL;

  data->expression.handler->getExpressionData(
    src,
    data->expression.data,
    data->expression.token,
    &expression,
    offset,
    data->expression.handler->id
  );

  // !TODO add expression overload
  if (expression.result_type.type_id != SYNTAX_TYPE_ID_INT) {
    throwSourceError(src, "wrong expression type, expected int", token);
  }

  result->result_type = expression.result_type;
  result->child_expressions = newArray(ExpressionData, expression);
}

