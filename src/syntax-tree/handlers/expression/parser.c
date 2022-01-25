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
#include "syntax-tree/handlers/while/parser.h"
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
      &parseWhile,
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
      &parseAssignation,
    );
  }
  return left_expressions;
}

static List *parseLeftExpression(
  List *start_token,
  SyntaxNode *left,
  SyntaxNode *result,
  char **error,
  bool allow_void,
  int min_priority
) {
  Array *expressions = getLeftExpressions();
  for (int i = 0; i != arrayGetLength(expressions); ++i) {
    *error = NULL;
    ChopLeftExpression chopLeftExpression = *(ChopLeftExpression*) arrayAt(expressions, i);

    List *token_end = chopLeftExpression(start_token, left, result, error);

    if (*error == NULL) {
      if (result->priority < min_priority) {
        continue;
      }
      if (!allow_void && result->handler->is_void_expression) {
        *error = "expression cannot be of type void";
      }
      return token_end;
    }
  }
  *error = "failed to parse left expression";
  return start_token;
}

List *parseExpression(List *start_token, SyntaxNode *result, char **error, bool allow_void, int min_priority) {
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
      if (result->priority < min_priority) {
        continue;
      }
      if (!allow_void && result->handler->is_void_expression) {
        *error = "expression cannot be of type void";
        return token_end;
      }
      for(;;) {
        SyntaxNode left_expression_result;
        List *new_token_end = parseLeftExpression(
          token_end,
          result,
          &left_expression_result,
          error,
          allow_void,
          min_priority
        );

        if (*error == NULL) {
          *result = left_expression_result;
          token_end = new_token_end;
          continue;
        }
        *error = NULL;
        return token_end;
      }
    }
  }
  *error = "unknown token";

  return current_token;
}
