#include <stdlib.h>
#include <stdio.h>

#include "utils/logger/log-src-error.h"
#include "../identifier/data.h"
#include "../function/data.h"
#include "./data.h"

void getFunctionCallExpressionData(
  void *raw_data,
  List *token,
  ExpressionData *result,
  int *offset,
  int handler_id
) {
  SyntaxFunctionCallData *data = (SyntaxFunctionCallData*) raw_data;
  expressionInit(result, EXPRESSION_FUNCTION_CALL, "function_call", token, false);
  result->compileX86 = compileFunctionCallX86;

  ExpressionData *target_expression = malloc(sizeof(ExpressionData));
  target_expression->parent_scope = result->parent_scope;

  data->target.handler->getExpressionData(
    data->target.data,
    data->target.token,
    target_expression,
    offset,
    data->target.handler->id
  );

  if (target_expression->result_type.type_id != TYPE_ID_FUNCTION) {
    char err[100];
    sprintf(err, "value of type \"%s\" is not callable", getTypeName(&(target_expression->result_type)));
    throwSourceError(err, target_expression->token);
  }

  FunctionTypeData *function_data = (FunctionTypeData*) target_expression->result_type.data;

  if (arrayGetLength(function_data->args) != arrayGetLength(data->arguments)) {
    throwSourceError("wrong number of arguments", token);
  }

  Array *args = createEmptyArray(arrayGetLength(data->arguments), sizeof(ExpressionData));

  for (int i = 0; i != arrayGetLength(data->arguments); ++i) {
    SyntaxNode *node = (SyntaxNode*) arrayAt(data->arguments, i);
    ExpressionData arg_expression;
    arg_expression.parent_scope = result->parent_scope;
    setVoidType(&(arg_expression.result_type));

    node->handler->getExpressionData(
      node->data,
      node->token,
      &arg_expression,
      offset,
      node->handler->id
    );

    VariableData *original_arg = (VariableData*) arrayAt(function_data->args, i);

    if (!isTypesCompatible(&(arg_expression.result_type), &(original_arg->type))) {
      char err[100];
      sprintf(
        err,
        "wrong type, expected type with id %d, got %d",
        original_arg->type.type_id,
        arg_expression.result_type.type_id
      );
      throwSourceError(err, node->token);
    }

    arrayPush(args, &arg_expression);
  }

  result->child_expressions = args;
  result->result_type = function_data->result_type;
  result->value = target_expression;

  return;
}
