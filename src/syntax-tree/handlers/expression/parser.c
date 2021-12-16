#include <stdlib.h>
#include <stdio.h>

#include "utils/array/array.h"
#include "syntax-tree/handlers/assignation/parser.h"
#include "syntax-tree/handlers/initialization/parser.h"
#include "syntax-tree/handlers/literal/parser.h"
#include "syntax-tree/syntax-helpers.h"

#include "./parser.h"

Array *expressions;
static Array *getExpressions() {
  if (expressions == NULL) {
    expressions = newArray(
      ChopExpression,
      &parseAssignation,
      &parseInitialization,
      &parseLiteral,
    );
  }
  return expressions;
}

List *parseExpression(List *first_token, SyntaxNode *result, char **error) {
  *error = NULL;
  Array *expressions = getExpressions();

  first_token = trimTokensLeft(first_token);
  if (first_token == NULL) {
    *error = "Failed to parse expression, programm ended";
    return first_token;
  }

  TokenData *token_data = (TokenData*) listGetValue(first_token);

  for (int i = 0; i != arrayGetLength(expressions); ++i) {
    ChopExpression chopExpression = *(ChopExpression*) arrayAt(expressions, i);
    *error = NULL;
    List *token_end = chopExpression(first_token, result, error);
    if (*error == NULL) {
      return token_end;
    }
  }
  *error = "Failed to parse expression";

  return first_token;
}
