#ifndef SYNTAX_DATA_IF_H
#define SYNTAX_DATA_IF_H

#include "syntax-tree/syntax-node.h"

typedef struct {
  SyntaxNode condition;
  SyntaxNode expression;
  SyntaxNode* else_expression;
} SyntaxIfData;

void printSyntaxIfData(SyntaxIfData *data);
void getIfExpressionData(
  const char *src,
  void *data,
  List *token,
  ExpressionData *result,
  int *offset,
  int handler_id
);

void compileIfX86(char *src, ExpressionData *self, bool address, FILE *out_stream);

#endif
