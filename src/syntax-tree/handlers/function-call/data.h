#ifndef SYNTAX_DATA_FUNCTION_CALL_H
#define SYNTAX_DATA_FUNCTION_CALL_H

#include "syntax-tree/syntax-node.h"

typedef struct {
  SyntaxNode target;
  Array *arguments; // array of syntax nodes (expressions)
} SyntaxFunctionCallData;

void printSyntaxFunctionCallData(SyntaxFunctionCallData *data);

#endif
