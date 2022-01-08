#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "utils/array/array.h"
#include "syntax-tree/handlers/assignation/parser.h"
#include "syntax-tree/handlers/function/parser.h"
#include "syntax-tree/handlers/function-call/parser.h"
#include "syntax-tree/handlers/parentheses/parser.h"
#include "syntax-tree/handlers/operation-prefix/parser.h"
#include "syntax-tree/handlers/operation-postfix/parser.h"
#include "syntax-tree/handlers/operation-lr/parser.h"
#include "syntax-tree/handlers/initialization/parser.h"
#include "syntax-tree/handlers/literal/parser.h"
#include "syntax-tree/handlers/identifier/parser.h"
#include "syntax-tree/handlers/scope/parser.h"
#include "syntax-tree/handlers/return/parser.h"
#include "syntax-tree/handlers/if/parser.h"
#include "syntax-tree/handlers/function-call/data.h"
#include "syntax-tree/syntax-helpers.h"

#include "./parser.h"

Array *expressions;
static Array *getExpressions() {
  if (expressions == NULL) {
    expressions = newArray(
      ChopExpression,
      &parseScope,
      &parseIf,
      &parseAssignation,
      &parseOperationPrefix,
      &parseParentheses,
      &parseInitialization,
      &parseLiteral,
      &parseIdentifier,
      &parseReturn,
      &parseFunction,
    );
  }
  return expressions;
}

Array *left_expressions;
static Array *getLeftExpressions() {
  if (left_expressions == NULL) {
    left_expressions = newArray(
      ChopLeftExpression,
      &parseOperation,
      &parseFunctionCall,
      &parseOperationPostfix,
    );
  }
  return left_expressions;
}

List *parseLeftExpression(List *start_token, SyntaxNode *left, SyntaxNode *result, char **error) {
  Array *expressions = getLeftExpressions();
  for (int i = 0; i != arrayGetLength(expressions); ++i) {
    *error = NULL;
    ChopLeftExpression chopLeftExpression = *(ChopLeftExpression*) arrayAt(expressions, i);

    List *token_end = chopLeftExpression(start_token, left, result, error);

    if (*error == NULL) {
      return token_end;
    }
  }
  *error = "failed to parse left expression";
  return start_token;
}

List *parseExpression(List *start_token, SyntaxNode *result, char **error) {
  *error = NULL;
  Array *expressions = getExpressions();

  List *current_token = trimTokensLeft(start_token);
  if (current_token == NULL) {
    *error = "Failed to parse expression, scope ended";
    return current_token;
  }

  for (int i = 0; i != arrayGetLength(expressions); ++i) {
    ChopExpression chopExpression = *(ChopExpression*) arrayAt(expressions, i);

    *error = NULL;
    List *token_end = chopExpression(current_token, result, error);
    if (*error == NULL) {
      SyntaxNode left_expression_result;
      List *new_token_end = parseLeftExpression(token_end, result, &left_expression_result, error);
      if (*error == NULL) {
        *result = left_expression_result;
        return new_token_end;
      }
      *error = NULL;
      return token_end;
    }
  }
  *error = "Failed to parse expression, unknown token";

  return current_token;
}
