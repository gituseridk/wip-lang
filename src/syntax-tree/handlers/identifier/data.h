#ifndef SYNTAX_DATA_IDENTIFIER_H
#define SYNTAX_DATA_IDENTIFIER_H

#include <stdbool.h>
#include "syntax-tree/syntax-node.h"

typedef struct {
  char *name;
} SyntaxIdentifierData;

void printSyntaxIdentifierData(SyntaxIdentifierData *data);

void getIdentifierExpressionData(
  const char *src,
  void *raw_data,
  List *token,
  ExpressionData *result,
  unsigned *offset,
  int handler_id
);

void compileIdentifierX86(char *src, ExpressionData *self, FILE *out_stream);

#endif
