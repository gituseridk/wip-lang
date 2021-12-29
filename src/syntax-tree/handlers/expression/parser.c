#include <stdlib.h>
#include <stdio.h>

#include "utils/array/array.h"
#include "syntax-tree/handlers/assignation/parser.h"
#include "syntax-tree/handlers/function/parser.h"
#include "syntax-tree/handlers/parentheses/parser.h"
#include "syntax-tree/handlers/operation-lr/parser.h"
#include "syntax-tree/handlers/initialization/parser.h"
#include "syntax-tree/handlers/literal/parser.h"
#include "syntax-tree/handlers/identifier/parser.h"
#include "syntax-tree/handlers/scope/parser.h"
#include "syntax-tree/syntax-helpers.h"

#include "./parser.h"

Array *expressions;
static Array *getExpressions() {
  if (expressions == NULL) {
    expressions = newArray(
      ChopExpression,
      &parseScope,
      &parseAssignation,
      &parseOperation,
      &parseParentheses,
      &parseInitialization,
      &parseLiteral,
      &parseIdentifier,
      &parseFunction,
    );
  }
  return expressions;
}

List *parseExpression(List *first_token, SyntaxNode *result, char **error, ChopExpression expression_to_execlude) {
  *error = NULL;
  Array *expressions = getExpressions();

  List *current_token = trimTokensLeft(first_token);
  if (current_token == NULL) {
    *error = "Failed to parse expression, scope ended";
    return current_token;
  }

  for (int i = 0; i != arrayGetLength(expressions); ++i) {
    ChopExpression chopExpression = *(ChopExpression*) arrayAt(expressions, i);
    if (chopExpression == expression_to_execlude) {
      continue;
    }
    *error = NULL;
    List *token_end = chopExpression(current_token, result, error);
    if (*error == NULL) {
      return token_end;
    }
  }
  *error = "Failed to parse expression, unknown token";

  return current_token;
}
