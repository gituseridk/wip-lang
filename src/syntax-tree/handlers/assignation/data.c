#include <stdio.h>

#include "./data.h"

void printSyntaxAssignationData(SyntaxAssignationData *data) {
  printf("{\"left\":");
  syntaxNodePrint(&(data->left));
  printf(",\"right\":");
  syntaxNodePrint(&(data->right));
  printf("}");
}
