#include <stdlib.h>

#include "utils/logger/log-src-error.h"
#include "./data.h"

void getIdentifierExpressionData(
  const char *src,
  void *raw_data,
  List *token,
  ExpressionData *result,
  int *offset,
  int handler_id
) {
  SyntaxIdentifierData *data = (SyntaxIdentifierData*) raw_data;
  expressionInit(result, EXPRESSION_IDENTIFIER, "identifier", token, false);
  result->compileX86 = compileIdentifierX86;

  unsigned scope_diff;
  VariableData *var_data = expressionDataGetVariable(result, data->name, &scope_diff);
  if (var_data == NULL) {
    throwSourceError(src, "ubdefined identifier", token);
  }

  ExpressionIdentifierValue *expression_value = (ExpressionIdentifierValue*) malloc(sizeof(ExpressionIdentifierValue));

  expression_value->var = var_data;
  expression_value->scope_diff = scope_diff;

  result->result_type = var_data->type;
  result->value = expression_value;
}
