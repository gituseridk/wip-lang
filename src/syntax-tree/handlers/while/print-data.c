#include <stdio.h>

#include "./data.h"

void printSyntaxWhileData(SyntaxWhileData *data) {
  printf("{\"condition\":");
  syntaxNodePrint(&(data->condition));
  printf(",\"expression\":");
  syntaxNodePrint(&(data->expression));
  printf("}");
}
