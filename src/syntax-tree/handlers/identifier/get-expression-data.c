#include <stdlib.h>

#include "utils/logger/log-src-error.h"
#include "./data.h"

void getIdentifierExpressionData(
  const char *src,
  void *raw_data,
  List *token,
  ExpressionData *result
) {
  SyntaxIdentifierData *data = (SyntaxIdentifierData*) raw_data;
  result->id = EXPRESSION_FUNCTION;

  VariableData *var_data = mapGet(result->parent_scope->variables, data->name);
  if (var_data == NULL) {
    throwSourceError(src, "ubdefined identifier", token);
  }

  result->result_type = var_data->result_type;
  result->value = var_data;
}
