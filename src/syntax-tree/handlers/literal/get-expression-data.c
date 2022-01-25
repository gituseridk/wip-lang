#include <stdlib.h>

#include "utils/logger/log-src-error.h"
#include "./data.h"

void getLiteralExpressionData(
  void *raw_data,
  List *token,
  ExpressionData *result,
  int *offset,
  int handler_id
) {
  SyntaxLiteralData *data = (SyntaxLiteralData*) raw_data;
  expressionInit(result, EXPRESSION_LITERAL, "literal", token, false);
  result->compileX86 = compileLiteralX86;

  result->value = data->value;
  result->result_type = data->type_definition;
}

