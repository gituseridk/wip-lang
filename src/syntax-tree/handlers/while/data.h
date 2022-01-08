#ifndef SYNTAX_DATA_WHILE_H
#define SYNTAX_DATA_WHILE_H

#include "syntax-tree/syntax-node.h"

typedef struct {
  SyntaxNode condition;
  SyntaxNode expression;
} SyntaxWhileData;

void printSyntaxWhileData(SyntaxWhileData *data);
void getWhileExpressionData(
  const char *src,
  void *data,
  List *token,
  ExpressionData *result,
  unsigned *offset,
  int handler_id
);

#endif
