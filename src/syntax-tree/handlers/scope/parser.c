#include <stdlib.h>
#include <stdio.h>

#include "syntax-tree/syntax-helpers.h"
#include "syntax-tree/handlers/expression/parser.h"

#include "./data.h"
#include "./parser.h"

static List *chopBracket(List *start_token, char **error, bool open) {
  List *current_token = trimTokensLeftHard(start_token);
  if (current_token == NULL) {
    *error = "Failed to parse scope, end of program";
    return current_token;
  }
  TokenData *token_data = (TokenData*) listGetValue(current_token);

  int bracket_id = open ? TOKEN_BRACKET_OPEN : TOKEN_BRACKET_CLOSE;
  char bracket_value = open ? '{' : '}';
  
  if (token_data->token.id != bracket_id || *(token_data->value) != bracket_value) {
    *error = open
      ? "Failed to parse scope, miss open bracket"
      : "Failed to parse scope, miss closing bracket";
    return start_token;
  }

  return listNext(current_token);
}

static List *parseScopeExpressions(List *tokens, SyntaxNode *result, char **error, bool with_brackets) {
  *error = NULL;
  tokens = trimTokensLeft(tokens);
  result->token = tokens;

  if (with_brackets) {
    tokens = chopBracket(tokens, error, true);
    if (*error != NULL) {
      return tokens;
    }
  }

  SyntaxScopeData *data = (SyntaxScopeData*) malloc(sizeof(SyntaxScopeData));
  *result = (SyntaxNode) {
    .data = data,
    .handler = getSyntaxNodeHandler(SYNTAX_SCOPE),
  };

  data->nodes = createEmptyArray(1, sizeof(SyntaxNode));

  List *current_token = tokens;
  while (current_token != NULL) {
    if (with_brackets) {
      List *token_after_bracket = chopBracket(current_token, error, false);
      if (*error == NULL) {
        *error = NULL;
        return token_after_bracket;
      }
      *error = NULL;
    }

    SyntaxNode node;
    current_token = trimTokensLeftHard(current_token);
    current_token = parseExpression(current_token, &node, error, NULL);
    if (*error != NULL) {
      return current_token;
    }
    current_token = chopExpressionEnd(current_token, error);
    if (*error != NULL) {
      return current_token;
    }
    arrayPush(data->nodes, &node);
    current_token = trimTokensLeftHard(current_token);
  }

  if (with_brackets) {
    *error = "Failed to parse scope, miss closing bracket";
  }

  return current_token;
}

List *parseScopeGlobal(List *tokens, SyntaxNode *result, char **error) {
  return parseScopeExpressions(tokens, result, error, false);
}

List *parseScope(List *tokens, SyntaxNode *result, char **error) {
  return parseScopeExpressions(tokens, result, error, true);
}
