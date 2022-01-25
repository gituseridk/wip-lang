#ifndef SYNTAX_DATA_WHILE_H
#define SYNTAX_DATA_WHILE_H

#include "syntax-tree/syntax-node.h"

typedef struct {
  SyntaxNode condition;
  SyntaxNode expression;
} SyntaxWhileData;

void printSyntaxWhileData(SyntaxWhileData *data);
void getWhileExpressionData(
  void *data,
  List *token,
  ExpressionData *result,
  int *offset,
  int handler_id
);

void compileWhileX86(ExpressionData *self, bool address, FILE *out_stream);

#endif
