#include <stdlib.h>

#include "utils/logger/log-src-error.h"
#include "../scope/data.h"
#include "./data.h"

unsigned last_function_id = 0;

void getFunctionExpressionData(
  void *raw_data,
  List *token,
  ExpressionData *result,
  int *paret_offset,
  int handler_id
) {
  int offset = 8;
  SyntaxFunctionData *data = (SyntaxFunctionData*) raw_data;
  expressionInit(result, EXPRESSION_FUNCTION, "function", token, true);
  asprintf(&(result->scope_label), "function_%d", last_function_id++);
  result->compileX86 = compileFunctionX86;

  FunctionTypeData *function_type_data = malloc(sizeof(FunctionTypeData));
  function_type_data->args = createEmptyArray(arrayGetLength(data->arguments), sizeof(VariableData));
  function_type_data->label = result->scope_label;

  int arg_offset = data->return_type.type_id == TYPE_ID_VOID ? -8: -8 - TYPE_SIZE_POINTER;
  for (int i = 0; i != arrayGetLength(data->arguments); ++i) {
    FunctionArgument *arg = (FunctionArgument*)arrayAt(data->arguments, i);
    if (mapGet(result->variables, arg->name) != NULL) {
      throwSourceError("name is already used in this scope", arg->token);
    }
    arg_offset -= getTypeSize(&(arg->type_definition));
    VariableData data = (VariableData) {
      .scope = result,
      .name = arg->name,
      .type = arg->type_definition,
      .scope_offset = arg_offset,
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
    data->body_expression.data,
    data->body_expression.token,
    &body,
    &offset,
    data->body_expression.handler->id
  );

  if (!isTypesCompatible(&(body.result_type), &(data->return_type))) {
    throwSourceError("the return type of the function is invalid", data->body_expression.token);
  }

  result->child_expressions = newArray(ExpressionData, body);
}
