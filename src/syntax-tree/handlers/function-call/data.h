#ifndef SYNTAX_DATA_FUNCTION_CALL_H
#define SYNTAX_DATA_FUNCTION_CALL_H

#include "syntax-tree/syntax-node.h"

typedef struct {
  SyntaxNode target;
  Array *arguments; // array of syntax nodes (expressions)
} SyntaxFunctionCallData;

void printSyntaxFunctionCallData(SyntaxFunctionCallData *data);

void getFunctionCallExpressionData(
  const char *src,
  void *raw_data,
  List *token,
  ExpressionData *result,
  unsigned *offset,
  int handler_id
);

void compileFunctionCallX86(char *src, ExpressionData *self, FILE *out_stream);

#endif
