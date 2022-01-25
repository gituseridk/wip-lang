#ifndef SYNTAX_DATA_OPERATION_PREFIX_H
#define SYNTAX_DATA_OPERATION_PREFIX_H

#include "syntax-tree/syntax-node.h"

enum OperatioPrefixIds {
  OPERATION_PREFIX_ID_INC,
  OPERATION_PREFIX_ID_DEC,
  OPERATION_PREFIX_ID_DEREFERENCING,
  OPERATION_PREFIX_ID_NEGOTATION,

  OPERATION_PREFIX_IDS_END,
};

typedef struct {
  int operation_id;
  SyntaxNode expression;
} SyntaxOperationPrefixData;

void printSyntaxOperationPrefixData(SyntaxOperationPrefixData *data);

void getOperationPrefixExpressionData(
  void *raw_data,
  List *token,
  ExpressionData *result,
  int *offset,
  int handler_id
);

void compileOperationPrefixX86(ExpressionData *self, bool address, FILE *out_stream);

#endif
