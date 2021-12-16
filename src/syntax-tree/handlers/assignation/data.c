#include <stdio.h>

#include "./data.h"

void printSyntaxAssignationData(SyntaxAssignationData *data) {
  printf("{left:");
  data->left.print(&(data->left));
  printf(",right:");
  data->right.print(&(data->right));
  printf("}");
}
