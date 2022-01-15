#ifndef SYNTAX_DATA_OPERATION_H
#define SYNTAX_DATA_OPERATION_H

#include "syntax-tree/syntax-node.h"

#define OPERATION_ID_SUM                0
#define OPERATION_ID_DIFFERENCE         1
#define OPERATION_ID_RATIO              2
#define OPERATION_ID_PRODUCT            3
#define OPERATION_ID_BIT_OR             4
#define OPERATION_ID_BIT_AND            5
#define OPERATION_ID_AND                6
#define OPERATION_ID_OR                 7
#define OPERATION_ID_EQUALS             8
#define OPERATION_ID_NOT_EQUALS         9
#define OPERATION_ID_EQUALS_STRICT      10
#define OPERATION_ID_NOT_EQUALS_STRICT  11
#define OPERATION_ID_GRATER_OR_EQUAL    12
#define OPERATION_ID_LESS_OR_EQUAL      13
#define OPERATION_ID_GRATER             14
#define OPERATION_ID_LESS               15

#define OPERATION_LR_COUNT              16

typedef struct {
  int operation_id;
  SyntaxNode left;
  SyntaxNode right;
} SyntaxOperationData;

void printSyntaxOperationLRData(SyntaxOperationData *data);

void getOperationLRExpressionData(
  const char *src,
  void *raw_data,
  List *token,
  ExpressionData *result,
  int *offset,
  int handler_id
);

void compileOperationLRX86(char *src, ExpressionData *self, bool address, FILE *out_stream);

#endif
