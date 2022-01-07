#include <stdlib.h>

#include "./expression-data.h"

VariableData *expressionDataGetVariable(ExpressionData *self, char *name) {
  while (self != NULL) {
    VariableData *var_data = mapGet(self->variables, name);
    if (var_data != NULL) {
      return var_data;
    }
    self = self->parent_scope;
  }
  return NULL;
}
