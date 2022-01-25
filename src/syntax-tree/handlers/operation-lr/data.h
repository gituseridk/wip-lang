#ifndef SYNTAX_DATA_OPERATION_H
#define SYNTAX_DATA_OPERATION_H

#include "syntax-tree/syntax-node.h"

enum OperationLrIds {
  OPERATION_ID_AND,
  OPERATION_ID_OR,

  OPERATION_ID_EQUALS,
  OPERATION_ID_NOT_EQUALS,
  OPERATION_ID_EQUALS_STRICT,
  OPERATION_ID_NOT_EQUALS_STRICT,
  OPERATION_ID_GRATER_OR_EQUAL,
  OPERATION_ID_LESS_OR_EQUAL,
  OPERATION_ID_GRATER,
  OPERATION_ID_LESS,

  OPERATION_ID_SUM,
  OPERATION_ID_DIFFERENCE,

  OPERATION_ID_RATIO,
  OPERATION_ID_PRODUCT,

  OPERATION_ID_BIT_OR,
  OPERATION_ID_BIT_AND,

  OPERATION_ID_END,
};

typedef struct {
  int operation_id;
  SyntaxNode left;
  SyntaxNode right;
} SyntaxOperationData;

void printSyntaxOperationLRData(SyntaxOperationData *data);

void getOperationLRExpressionData(
  void *raw_data,
  List *token,
  ExpressionData *result,
  int *offset,
  int handler_id
);

void compileOperationLRX86(ExpressionData *self, bool address, FILE *out_stream);

#endif
