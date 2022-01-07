#include <stdlib.h>

#include "utils/logger/log-src-error.h"
#include "./data.h"

static VariableData *getVarData(ExpressionData *expression, char *name) {
  while (expression != NULL) {
    VariableData *var_data = mapGet(expression->variables, name);
    if (var_data != NULL) {
      return var_data;
    }
    expression = expression->parent_scope;
  }
  return NULL;
}

void getIdentifierExpressionData(
  const char *src,
  void *raw_data,
  List *token,
  ExpressionData *result,
  unsigned *offset,
  int handler_id
) {
  SyntaxIdentifierData *data = (SyntaxIdentifierData*) raw_data;
  result->id = EXPRESSION_FUNCTION;
  result->variables = createMap(sizeof(VariableData));

  VariableData *var_data = getVarData(result, data->name);
  if (var_data == NULL) {
    throwSourceError(src, "ubdefined identifier", token);
  }

  result->result_type = var_data->result_type;
  result->value = var_data;
}
