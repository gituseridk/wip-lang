#include "./expression-data.h"

unsigned expressionGetSize(ExpressionData *self) {
  unsigned size = 0;
  for (MapItterator *i = mapBegin(self->variables); !mapItteratorIsEnded(i); mapItteratorNext(i)) {
    VariableData *var = (VariableData*) mapItteratorGet(i).value;
    size += var->scope_offset;
  }
  return size;
}
