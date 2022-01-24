#include <stdio.h>

#include "./data.h"

void printSyntaxIfData(SyntaxIfData *data) {
  printf("{\"condition\":");
  syntaxNodePrint(&(data->condition));
  printf(",\"expression\":");
  syntaxNodePrint(&(data->expression));
  printf(",\"else_expression\":");
  if (data->else_expression != NULL) {
    syntaxNodePrint(data->else_expression);
  } else {
    printf("null");
  }
  printf("}");
}
