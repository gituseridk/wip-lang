#include <stdio.h>

#include "./data.h"

void printSyntaxInitializationData(SyntaxInitializationData *data) {
  printf("{\"initialization\":\"%s\",\"is_constant\":%d}", data->identifier, data->is_constant);
}
