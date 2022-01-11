#include <stdlib.h>

#include "utils/logger/log-src-error.h"
#include "./data.h"

void getLiteralExpressionData(
  const char *src,
  void *raw_data,
  List *token,
  ExpressionData *result,
  unsigned *offset,
  int handler_id
) {
  SyntaxLiteralData *data = (SyntaxLiteralData*) raw_data;
  expressionInit(result, EXPRESSION_LITERAL, token, false);
  result->compileX86 = compileLiteralX86;
  
  result->value = data->value;
  result->result_type = data->type_definition;
}

