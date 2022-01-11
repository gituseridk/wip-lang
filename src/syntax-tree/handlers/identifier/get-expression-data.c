#include <stdlib.h>

#include "utils/logger/log-src-error.h"
#include "./data.h"

void getIdentifierExpressionData(
  const char *src,
  void *raw_data,
  List *token,
  ExpressionData *result,
  unsigned *offset,
  int handler_id
) {
  SyntaxIdentifierData *data = (SyntaxIdentifierData*) raw_data;
  expressionInit(result, EXPRESSION_FUNCTION, token);

  VariableData *var_data = expressionDataGetVariable(result, data->name);
  if (var_data == NULL) {
    throwSourceError(src, "ubdefined identifier", token);
  }

  result->result_type = var_data->type;
  result->value = var_data;
}
