#include <stdio.h>

#include "syntax-tree/syntax-node.h"
#include "./data.h"

void printNode(void *self, void *el, int index, const Array *array) {
  syntaxNodePrint(el);
  if (index != arrayGetLength(array) - 1) {
    printf(",");
  }
}

void printSyntaxScopeData(SyntaxScopeData *data) {
  printf("{\"nodes\":[");
  arrayForEach(data->nodes, printNode, NULL);
  printf("]}");
}
