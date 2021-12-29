#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <assert.h>

#include "utils/array/array.h"
#include "syntax-tree/handlers/assignation/parser.h"
#include "syntax-tree/handlers/function/parser.h"
#include "syntax-tree/handlers/parentheses/parser.h"
#include "syntax-tree/handlers/operation-lr/parser.h"
#include "syntax-tree/handlers/initialization/parser.h"
#include "syntax-tree/handlers/literal/parser.h"
#include "syntax-tree/handlers/identifier/parser.h"
#include "syntax-tree/handlers/scope/parser.h"
#include "syntax-tree/handlers/return/parser.h"
#include "syntax-tree/handlers/function-call/data.h"
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
      &parseReturn,
      &parseFunction,
    );
  }
  return expressions;
}

List *chopFunctionCall(List *start_token, SyntaxNode *result, char **error) {
  List *current_token = trimTokensLeft(start_token);
  current_token = chopToken(current_token, TOKEN_BRACKET_OPEN, "(", error);
  if (*error != NULL) {
    return current_token;
  }

  Array *arguments = createEmptyArray(1, sizeof(SyntaxNode));
  while (true) {
    SyntaxNode arg;
    current_token = parseExpression(current_token, &arg, error, NULL);
    if (*error != NULL) {
      arrayFree(arguments);
      return current_token;
    }
    arrayPush(arguments, &arg);

    current_token = trimTokensLeft(current_token);
    if (current_token == NULL) {
      arrayFree(arguments);
      *error = "Failed to parse argument, end of program";
      return current_token;
    }

    current_token = chopToken(current_token, TOKEN_SEPARATOR, ",", error);
    if (*error == NULL) {
      continue;
    }
    *error = NULL;

    current_token = chopToken(current_token, TOKEN_BRACKET_CLOSE, ")", error);
    if (*error == NULL) {
      SyntaxNode result_node;
      result_node.data = malloc(sizeof(SyntaxFunctionCallData));
      ((SyntaxFunctionCallData*)result_node.data)->target = *result;
      ((SyntaxFunctionCallData*)result_node.data)->arguments = arguments;
      result_node.handler = getSyntaxNodeHandler(SYNTAX_FUNCTION_CALL);

      *result = result_node;

      return current_token;
    }
    *error = NULL;
  }
  __builtin_unreachable();
}

List *parseExpression(List *start_token, SyntaxNode *result, char **error, ChopExpression expression_to_execlude) {
  *error = NULL;
  Array *expressions = getExpressions();

  List *current_token = trimTokensLeft(start_token);
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
      List *new_token_end = chopFunctionCall(token_end, result, error);
      if (*error == NULL) {
        return new_token_end;
      }
      *error = NULL;
      return token_end;
    }
  }
  *error = "Failed to parse expression, unknown token";

  return current_token;
}
