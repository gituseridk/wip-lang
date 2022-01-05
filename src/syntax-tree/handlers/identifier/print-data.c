#include <stdio.h>
#include "./data.h"

void printSyntaxIdentifierData(SyntaxIdentifierData *data) {
  printf("{\"name\":\"%s\"}", (char*) data->name);
}
