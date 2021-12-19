#ifndef SYNTAX_DATA_OPERATION_H
#define SYNTAX_DATA_OPERATION_H

#include "syntax-tree/syntax-node.h"

#define OPERATION_ID_SUM 0
#define OPERATION_ID_DIFFERENCE 1
#define OPERATION_ID_RATIO 2
#define OPERATION_ID_PRODUCT 3

typedef struct {
  int operation_id;
  SyntaxNode left;
  SyntaxNode right;
} SyntaxOperationData;

void printSyntaxOperationData(SyntaxOperationData *data);

#endif
