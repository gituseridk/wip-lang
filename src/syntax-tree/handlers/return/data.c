#include <stdio.h>

#include "./data.h"

void printSyntaxReturnData(SyntaxReturnData *data) {
  printf("{\"expression\":");
  syntaxNodePrint(&(data->expression));
  printf("}");
}
