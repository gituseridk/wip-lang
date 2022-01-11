#ifndef SYNTAX_DATA_ASSIGNITION_H
#define SYNTAX_DATA_ASSIGNITION_H

#include "syntax-tree/syntax-node.h"

typedef struct {
  SyntaxNode left;
  SyntaxNode right;
} SyntaxAssignationData;

void printSyntaxAssignationData(SyntaxAssignationData *data);
void getAssignationExpressionData(
  const char *src,
  void *data,
  List *token,
  ExpressionData *result,
  unsigned *offset,
  int handler_id
);

void compileAssignationX86(char *src, ExpressionData *self, FILE *out_stream);

#endif
