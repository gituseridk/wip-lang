#include <stdlib.h>

#include "./expression-data.h"

VariableData *expressionDataGetVariable(ExpressionData *self, char *name, unsigned *scope_diff) {
  if (scope_diff != NULL) {
    *scope_diff = 0;
  }
  
  while (self != NULL) {
    if (self->variables != NULL) {
      VariableData *var_data = mapGet(self->variables, name);
      if (var_data != NULL) {
        return var_data;
      }
      if (scope_diff != NULL) {
        ++*scope_diff;
      }
    }
    self = self->parent_scope;
  }
  return NULL;
}
