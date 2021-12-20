#include <stdio.h>

#include "./data.h"

void printSyntaxOperationLRData(SyntaxOperationData *data) {
  printf("{\"left\":");
  syntaxNodePrint(&(data->left));
  printf(",\"right\":");
  syntaxNodePrint(&(data->right));
  printf(",\"operation_id\": %d", data->operation_id);
  printf("}");
}
