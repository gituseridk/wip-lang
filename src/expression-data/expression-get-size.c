#include "./expression-data.h"

unsigned expressionGetSize(ExpressionData *self) {
  if (self->variables == NULL) {
    return expressionGetSize(self->parent_scope);
  }

  unsigned size = 0;
  for (MapItterator *i = mapBegin(self->variables); !mapItteratorIsEnded(i); mapItteratorNext(i)) {
    VariableData *var = (VariableData*) mapItteratorGet(i).value;
    char *err = NULL;
    size += getTypeSize(&(var->type), &err);

    if (err != NULL) {
      printf("failed to allocate size on stack for type \"%s\"\n", getTypeName(&(var->type)));
    }
  }
  return size;
}
