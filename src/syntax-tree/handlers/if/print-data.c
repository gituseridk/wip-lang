#include <stdio.h>

#include "./data.h"

void printSyntaxIfData(SyntaxIfData *data) {
  printf("{\"condition\":");
  syntaxNodePrint(&(data->condition));
  printf(",\"expression\":");
  syntaxNodePrint(&(data->expression));
  printf("}");
}
