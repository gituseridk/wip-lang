#include <stdio.h>

#include "./data.h"

static void printArgument(void *self, void *element, int index, const Array *array) {
  syntaxNodePrint((SyntaxNode*) element);
  if (index != arrayGetLength(array) - 1) {
    printf(",");
  }
}

void printSyntaxFunctionCallData(SyntaxFunctionCallData *data) {
  printf("{\"target\":");
  syntaxNodePrint(&(data->target));
  printf(",\"arguments\":[");
  arrayForEach(data->arguments, printArgument, NULL);
  printf("]}");
}
