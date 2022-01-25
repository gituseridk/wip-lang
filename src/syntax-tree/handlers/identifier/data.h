#ifndef SYNTAX_DATA_IDENTIFIER_H
#define SYNTAX_DATA_IDENTIFIER_H

#include <stdbool.h>
#include "syntax-tree/syntax-node.h"

typedef struct
{
  unsigned scope_diff;
  VariableData *var;
} ExpressionIdentifierValue;


typedef struct {
  char *name;
} SyntaxIdentifierData;

void printSyntaxIdentifierData(SyntaxIdentifierData *data);

void getIdentifierExpressionData(
  void *raw_data,
  List *token,
  ExpressionData *result,
  int *offset,
  int handler_id
);

void compileIdentifierX86(ExpressionData *self, bool address, FILE *out_stream);

#endif
