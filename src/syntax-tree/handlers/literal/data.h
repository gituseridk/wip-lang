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
  void *raw_data,
  List *token,
  ExpressionData *result,
  int *offset,
  int handler_id
);

void compileLiteralX86(ExpressionData *self, bool address, FILE *out_stream);

#endif
