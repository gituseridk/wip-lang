#include "./expression-data.h"

void expressionInit(ExpressionData *result, int id, List *token) {
  result->id = id;
  result->token = token;
  result->variables = createMap(sizeof(VariableData));
  result->compileX86 = NULL;
}
