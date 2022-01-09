#include <stdio.h>

#include "./data.h"

void printSyntaxInitializationData(SyntaxInitializationData *data) {
  printf("{\"initialization\":\"%s\",\"is_constant\":%d,\"type\":", data->identifier, data->is_constant);
  if (data->type != NULL) {
    printTypeDefinition(data->type);
  } else {
    printf("null");
  }
  printf("}");
}
