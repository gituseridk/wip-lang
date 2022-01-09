#include <stdio.h>

#include "./syntax-node.h"

void syntaxNodePrint(SyntaxNode *self) {
  printf("{\"%s\":", self->handler->name);
  self->handler->printData(self->data);
  printf("}");
}
