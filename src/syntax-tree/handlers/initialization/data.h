#ifndef SYNTAX_DATA_INITIALISATION_H
#define SYNTAX_DATA_INITIALISATION_H

#include <stdbool.h>
#include "syntax-tree/syntax-node.h"

typedef struct {
  bool is_constant;
  TypeDefinition *type;
  char *identifier;
} SyntaxInitializationData;

void printSyntaxInitializationData(SyntaxInitializationData *data);
void getInitializationExpressionData(
  const char *src,
  void *raw_data,
  List *token,
  ExpressionData *result,
  int *offset,
  int handler_id
);

void compileInitializationX86(char *src, ExpressionData *self, bool address, FILE *out_stream);

#endif
