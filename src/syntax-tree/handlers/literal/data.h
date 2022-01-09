#ifndef SYNTAX_DATA_LITERAL_H
#define SYNTAX_DATA_LITERAL_H

#include <stdbool.h>
#include "syntax-tree/syntax-node.h"


typedef struct {
  TypeDefinition type_definition;
  void *value;
} SyntaxLiteralData;

void printSyntaxLiteralData(SyntaxLiteralData *data);
void getLiteralExpressionData(
  const char *src,
  void *raw_data,
  List *token,
  ExpressionData *result,
  unsigned *offset,
  int handler_id
);

#endif
