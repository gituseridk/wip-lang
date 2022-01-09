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
  int handler_id
) {
  SyntaxFunctionData *data = (SyntaxFunctionData*) raw_data;
  result->id = EXPRESSION_FUNCTION;
  result->variables = createMap(sizeof(VariableData));

  FunctionTypeData *function_type_data = malloc(sizeof(FunctionTypeData));
  function_type_data->args = createEmptyArray(arrayGetLength(data->arguments), sizeof(VariableData));

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
    arrayPush(function_type_data->args, &data);
  }

  function_type_data->result_type = data->return_type;

  result->result_type.type_id = TYPE_ID_FUNCTION;
  result->result_type.data = function_type_data;

  ExpressionData body;
  body.result_type = data->return_type;
  body.parent_scope = result;

  data->body_expression.handler->getExpressionData(
    src,
    data->body_expression.data,
    data->body_expression.token,
    &body,
    offset,
    data->body_expression.handler->id
  );

  if (!isSameType(&(body.result_type), &(data->return_type))) {
    throwSourceError(src, "the return type of the function is invalid", data->body_expression.token);
  }

  result->child_expressions = newArray(ExpressionData, body);
}
