#ifndef SYNTAX_DATA_RETURN_H
#define SYNTAX_DATA_RETURN_H

#include "syntax-tree/syntax-node.h"

typedef struct {
  SyntaxNode expression;
} SyntaxReturnData;

void printSyntaxReturnData(SyntaxReturnData *data);

#endif
