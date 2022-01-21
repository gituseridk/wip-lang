#include "./expression-data.h"
#include "token/token-data.h"

int getFunctionScopeLevel(ExpressionData *self) {
  unsigned result = 0;
  while (self != NULL) {
    if (self->id == EXPRESSION_FUNCTION) {
      return result;
    }
    
    self = self->parent_scope;
    ++result;
  }
  return -1;
}
