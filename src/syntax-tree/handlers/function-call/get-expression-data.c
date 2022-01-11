#include <stdlib.h>
#include <stdio.h>

#include "utils/logger/log-src-error.h"
#include "../identifier/data.h"
#include "../function/data.h"
#include "./data.h"

void getFunctionCallExpressionData(
  const char *src,
  void *raw_data,
  List *token,
  ExpressionData *result,
  unsigned *offset,
  int handler_id
) {
  SyntaxFunctionCallData *data = (SyntaxFunctionCallData*) raw_data;
  expressionInit(result, EXPRESSION_FUNCTION_CALL, "function_call", token, false);
  result->compileX86 = compileFunctionCallX86;

  if (data->target.handler->id == SYNTAX_IDENTIFIER) {
    char *identifier_name = ((SyntaxIdentifierData*) data->target.data)->name;
    
    VariableData *var = expressionDataGetVariable(result->parent_scope, identifier_name);

    if (var == NULL) {
      char err[100];
      sprintf(err, "\"%s\" is not defined", identifier_name);
      throwSourceError(src, err, token);
    }

    FunctionTypeData *function_data = (FunctionTypeData*) var->type.data;

    if (arrayGetLength(function_data->args) != arrayGetLength(data->arguments)) {
      throwSourceError(src, "wrong number off arguments", token);
    }

    Array *args = createEmptyArray(arrayGetLength(data->arguments), sizeof(ExpressionData));
    for (int i = 0; i != arrayGetLength(data->arguments); ++i) {
      SyntaxNode *node = (SyntaxNode*) arrayAt(data->arguments, i);
      ExpressionData arg_expression;
      arg_expression.parent_scope = result->parent_scope;
      arg_expression.result_type.type_id = TYPE_ID_VOID;
      arg_expression.result_type.data = NULL;

      node->handler->getExpressionData(
        src,
        node->data,
        node->token,
        &arg_expression,
        offset,
        node->handler->id
      );

      VariableData *original_arg = (VariableData*) arrayAt(function_data->args, i);

      if (!isSameType(&(arg_expression.result_type), &(original_arg->type))) {
        char err[100];
        sprintf(
          err,
          "wrong type, expected type with id %d, got %d",
          original_arg->type.type_id,
          arg_expression.result_type.type_id
        );
        throwSourceError(src, err, node->token);
      }

      arrayPush(args, &arg_expression);
    }

    result->child_expressions = args;
    result->result_type = function_data->result_type;

    return;
  }
  
  throwSourceError(src, "expression is not a function", token);
}
