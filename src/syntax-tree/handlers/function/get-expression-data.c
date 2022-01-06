#include <stdlib.h>

#include "utils/logger/log-src-error.h"
#include "../scope/data.h"
#include "./data.h"

void getFunctionExpressionData(
  const char *src,
  void *raw_data,
  List *token,
  ExpressionData *result
) {
  SyntaxFunctionData *data = (SyntaxFunctionData*) raw_data;
  result->id = EXPRESSION_FUNCTION;

  result->result_type.type_id = SYNTAX_TYPE_ID_FUNCTION;
  result->result_type.data = NULL; // !TODO add function type

  ExpressionData body;
  body.result_type = data->return_type;
  body.parent_scope = result->parent_scope;

  data->body_expression.handler->getExpressionData(
    src,
    data->body_expression.data,
    data->body_expression.token,
    &body
  );

  if (body.result_type.type_id != data->return_type.type_id || body.result_type.data != data->return_type.data) {
    throwSourceError(src, "the return type of the function is invalid", data->body_expression.token);
  }

  result->child_expressions = newArray(ExpressionData, body);
}
