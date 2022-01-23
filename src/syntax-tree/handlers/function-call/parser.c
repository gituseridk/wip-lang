#include <stdlib.h>

#include "syntax-tree/syntax-helpers.h"
#include "syntax-tree/handlers/expression/parser.h"
#include "./data.h"
#include "./parser.h"

List *parseFunctionCall(List *start_token, SyntaxNode *left, SyntaxNode *result, char **error) {
  List *current_token = trimTokensLeft(start_token);
  if (current_token == NULL) {
    *error = "failed to parse function call, end of program";
    return current_token;
  }
  current_token = chopToken(current_token, TOKEN_BRACKET_OPEN, "(", error);
  if (*error != NULL) {
    return current_token;
  }

  current_token = chopToken(current_token, TOKEN_BRACKET_CLOSE, ")", error);
  if (*error == NULL) {
    SyntaxNode result_node;
    result_node.priority = SYNTAX_FUNCTION_CALL * SYNTAX_PRIORITY_OFFSET;
    result_node.token = trimTokensLeft(start_token);
    result_node.data = malloc(sizeof(SyntaxFunctionCallData));
    ((SyntaxFunctionCallData*)result_node.data)->target = *left;
    ((SyntaxFunctionCallData*)result_node.data)->arguments = createEmptyArray(0, sizeof(SyntaxNode));
    result_node.handler = getSyntaxNodeHandler(SYNTAX_FUNCTION_CALL);

    *result = result_node;

    return current_token;
  } else {
    *error = NULL;
  }

  Array *arguments = createEmptyArray(1, sizeof(SyntaxNode));
  while (true) {
    SyntaxNode arg;
    current_token = parseExpression(current_token, &arg, error, false, 0);
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
      result_node.priority = SYNTAX_FUNCTION_CALL * SYNTAX_PRIORITY_OFFSET;
      result_node.token = trimTokensLeft(start_token);
      result_node.data = malloc(sizeof(SyntaxFunctionCallData));
      ((SyntaxFunctionCallData*)result_node.data)->target = *left;
      ((SyntaxFunctionCallData*)result_node.data)->arguments = arguments;
      result_node.handler = getSyntaxNodeHandler(SYNTAX_FUNCTION_CALL);

      *result = result_node;

      return current_token;
    }
    *error = NULL;
  }
  __builtin_unreachable();
}
