#ifndef SYNTAX_DATA_RETURN_H
#define SYNTAX_DATA_RETURN_H

#include "syntax-tree/syntax-node.h"

typedef struct {
  unsigned scope_level;
} ReturnExpressionData;


typedef struct {
  SyntaxNode *expression;
} SyntaxReturnData;

void printSyntaxReturnData(SyntaxReturnData *data);
void getReturnExpressionData(
  void *raw_data,
  List *token,
  ExpressionData *result,
  int *offset,
  int handler_id
);

void compileReturnX86(ExpressionData *self, bool address, FILE *out_stream);

#endif
