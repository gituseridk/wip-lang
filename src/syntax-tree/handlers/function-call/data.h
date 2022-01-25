#ifndef SYNTAX_DATA_FUNCTION_CALL_H
#define SYNTAX_DATA_FUNCTION_CALL_H

#include "syntax-tree/syntax-node.h"

typedef struct {
  SyntaxNode target;
  Array *arguments; // array of syntax nodes (expressions)
} SyntaxFunctionCallData;

void printSyntaxFunctionCallData(SyntaxFunctionCallData *data);

void getFunctionCallExpressionData(
  void *raw_data,
  List *token,
  ExpressionData *result,
  int *offset,
  int handler_id
);

void compileFunctionCallX86(ExpressionData *self, bool address, FILE *out_stream);

#endif
