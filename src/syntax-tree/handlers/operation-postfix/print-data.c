#include <stdio.h>

#include "./data.h"

void printSyntaxOperationPostfixData(SyntaxOperationPostfixData *data) {
  printf("{\"expression\":");
  syntaxNodePrint(&(data->expression));
  printf(",\"operation_id\": %d", data->operation_id);
  printf("}");
}
