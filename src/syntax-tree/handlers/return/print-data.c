#include <stdio.h>

#include "./data.h"

void printSyntaxReturnData(SyntaxReturnData *data) {
  printf("{\"expression\":");
  if (data->expression == NULL) {
    printf("null");
  } else {
    syntaxNodePrint(data->expression);
  }
  printf("}");
}
