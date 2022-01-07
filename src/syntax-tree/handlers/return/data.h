#ifndef SYNTAX_DATA_RETURN_H
#define SYNTAX_DATA_RETURN_H

#include "syntax-tree/syntax-node.h"

typedef struct {
  SyntaxNode *expression;
} SyntaxReturnData;

void printSyntaxReturnData(SyntaxReturnData *data);
void getReturnExpressionData(
  const char *src,
  void *raw_data,
  List *token,
  ExpressionData *result,
  unsigned *offset,
  int handler_id
);

#endif
