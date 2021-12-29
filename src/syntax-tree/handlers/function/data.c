#include <stdio.h>

#include "./data.h"

void printArgument(void *self, void *element, int index, const Array *array) {
  FunctionArgument *argument = (FunctionArgument*) element;

  printf("{\"name\":\"%s\",\"type_definition\":", argument->name);
  printSyntaxTypeDefinitionData(&(argument->type_definition));
  printf("}");
  if (index != arrayGetLength(array) - 1) {
    printf(",");
  }
}

void printSyntaxFunctionData(SyntaxFunctionData *data) {
  printf("{\"arguments\":[");

  arrayForEach(data->arguments, printArgument, NULL);

  printf("],\"body_expression\":");
  syntaxNodePrint(&(data->body_expression));
  printf("}");
}
