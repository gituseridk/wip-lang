#include <stdio.h>

#include "./data.h"

void printSyntaxOperationPrefixData(SyntaxOperationPrefixData *data) {
  printf("{\"expression\":");
  syntaxNodePrint(&(data->expression));
  printf(",\"operation_id\": %d", data->operation_id);
  printf("}");
}
