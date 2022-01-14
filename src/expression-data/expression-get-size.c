#include "./expression-data.h"

unsigned expressionGetSize(ExpressionData *self) {
  if (self->variables == NULL) {
    return expressionGetSize(self->parent_scope);
  }

  unsigned size = 0;
  for (MapItterator *i = mapBegin(self->variables); !mapItteratorIsEnded(i); mapItteratorNext(i)) {
    VariableData *var = (VariableData*) mapItteratorGet(i).value;
    size += getTypeSize(&(var->type));
  }
  return size;
}
