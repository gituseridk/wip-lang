#include <stdio.h>
#include "./data.h"

void printSyntaxLiteralData(SyntaxLiteralData *data) {
  printf("{\"type_id\":%d,\"value\":", data->type_id);
  if (data->type_id == SYNTAX_TYPE_ID_INT) {
    printf("%d}", *(int*) data->value);
    return;
  }
  if (data->type_id == SYNTAX_TYPE_ID_FLOAT) {
    printf("%f}", *(float*) data->value);
    return;
  }
  printf("null}");
}
