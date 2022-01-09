#include <stdio.h>
#include "./data.h"

void printSyntaxLiteralData(SyntaxLiteralData *data) {
  printf("{\"type\":");
  printTypeDefinition(&(data->type_definition));

  printf(",\"value\":");
  if (data->type_definition.type_id == TYPE_ID_INT) {
    printf("%d}", *(int*) data->value);
    return;
  }
  if (data->type_definition.type_id == TYPE_ID_FLOAT) {
    printf("%f}", *(float*) data->value);
    return;
  }
  printf("null}");
}
