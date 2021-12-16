#include <stdio.h>

#include "syntax-tree/syntax-node.h"
#include "./data.h"

void printNode(void *self, void *el, int index, const Array *array) {
  ((SyntaxNode*) el)->print(el);
  if (index != arrayGetLength(array) - 1) {
    printf(",");
  }
}

void printSyntaxProgramData(SyntaxProgramData *data) {
  printf("{nodes:[");
  arrayForEach(data->nodes, printNode, NULL);
  printf("]}");
}
