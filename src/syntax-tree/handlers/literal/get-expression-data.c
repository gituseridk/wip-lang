#include <stdlib.h>

#include "utils/logger/log-src-error.h"
#include "./data.h"

void getLiteralExpressionData(
  const char *src,
  void *raw_data,
  List *token,
  ExpressionData *result
) {
  SyntaxLiteralData *data = (SyntaxLiteralData*) raw_data;
  result->id = EXPRESSION_LITERAL;
  result->value = data->value;
  result->result_type = data->type_definition;
}

