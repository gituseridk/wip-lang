#include <stdlib.h>

#include "utils/logger/log-src-error.h"
#include "./data.h"

void getLiteralExpressionData(
  const char *src,
  void *raw_data,
  List *token,
  ExpressionData *result,
  unsigned *offset
) {
  SyntaxLiteralData *data = (SyntaxLiteralData*) raw_data;
  result->id = EXPRESSION_LITERAL;
  result->variables = createMap(sizeof(VariableData));
  result->value = data->value;
  result->result_type = data->type_definition;
}

