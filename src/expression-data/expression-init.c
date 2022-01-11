#include "./expression-data.h"

void expressionInit(
  ExpressionData *result,
  int id,
  List *token,
  bool is_scope
) {
  result->id = id;
  result->token = token;
  result->variables = is_scope ? createMap(sizeof(VariableData)) : NULL;
  result->compileX86 = NULL;
}
