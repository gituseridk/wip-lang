#ifndef SYNTAX_DATA_IF_H
#define SYNTAX_DATA_IF_H

#include "syntax-tree/syntax-node.h"

typedef struct {
  SyntaxNode condition;
  SyntaxNode expression;
} SyntaxIfData;

void printSyntaxIfData(SyntaxIfData *data);
void getIfExpressionData(
  const char *src,
  void *data,
  List *token,
  ExpressionData *result,
  unsigned *offset,
  int handler_id
);

#endif
