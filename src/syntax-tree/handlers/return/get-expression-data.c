#include <stdlib.h>
#include <stdio.h>

#include "utils/logger/log-src-error.h"
#include "syntax-tree/syntax-node.h"
#include "syntax-tree/syntax-helpers.h"
#include "./data.h"

// !TODO typechecking
void getReturnExpressionData(
  const char *src,
  void *raw_data,
  List *token,
  ExpressionData *result,
  int *offset,
  int handler_id
) {
  SyntaxReturnData *data = (SyntaxReturnData*)raw_data;
  expressionInit(result, EXPRESSION_RETURN, "return", token, false);
  result->compileX86 = compileReturnX86;

  if (data->expression == NULL) {
    return;
  }
  
  ExpressionData child_expression;
  child_expression.parent_scope = result->parent_scope;
  setVoidType(&(child_expression.result_type));

  data->expression->handler->getExpressionData(
    src,
    data->expression->data,
    data->expression->token,
    &child_expression,
    offset,
    data->expression->handler->id
  );

  int scope_level = getFunctionScopeLevel(result->parent_scope);
  if (scope_level < 0) {
    throwSourceError(src, "unexpected return", token);
  }
  ReturnExpressionData *value = malloc(sizeof(ReturnExpressionData));
  value->scope_level = scope_level;
  
  result->value = value;
  result->child_expressions = newArray(ExpressionData, child_expression);
}
