#include <stdlib.h>

#include "utils/logger/log-src-error.h"
#include "../scope/data.h"
#include "./data.h"

void getFunctionExpressionData(
  const char *src,
  void *raw_data,
  List *token,
  ExpressionData *result,
  unsigned *offset,
  char *handler_name
) {
  SyntaxFunctionData *data = (SyntaxFunctionData*) raw_data;
  result->id = EXPRESSION_FUNCTION;
  result->variables = createMap(sizeof(VariableData));

  for (int i = 0; i != arrayGetLength(data->arguments); ++i) {
    FunctionArgument *arg = (FunctionArgument*)arrayAt(data->arguments, i);
    if (mapGet(result->variables, arg->name) != NULL) {
      throwSourceError(src, "name is already used in this scope", arg->token);
    }
    VariableData data = (VariableData) {
      .is_constant = true,
      .name = arg->name,
      .result_type = arg->type_definition,
      .scope_offset = 0, // !TODO add offset
    };
    mapSet(result->variables, arg->name, &data);
  }

  result->result_type.type_id = SYNTAX_TYPE_ID_FUNCTION;
  result->result_type.data = NULL; // !TODO add function type

  ExpressionData body;
  body.result_type = data->return_type;
  body.parent_scope = result;

  data->body_expression.handler->getExpressionData(
    src,
    data->body_expression.data,
    data->body_expression.token,
    &body,
    offset,
    data->body_expression.handler->name
  );

  if (body.result_type.type_id != data->return_type.type_id || body.result_type.data != data->return_type.data) {
    throwSourceError(src, "the return type of the function is invalid", data->body_expression.token);
  }

  result->child_expressions = newArray(ExpressionData, body);
}
