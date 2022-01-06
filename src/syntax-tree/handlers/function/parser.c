#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "utils/array/array.h"
#include "syntax-tree/handlers/expression/parser.h"
#include "syntax-tree/handlers/initialization/parser.h"
#include "syntax-tree/handlers/identifier/parser.h"
#include "syntax-tree/handlers/identifier/data.h"
#include "syntax-tree/handlers/literal/parser.h"
#include "syntax-tree/handlers/type-definition/parser.h"
#include "syntax-tree/handlers/scope/parser.h"
#include "syntax-tree/handlers/scope/data.h"
#include "syntax-tree/syntax-helpers.h"
#include "./parser.h"
#include "./data.h"

List* trimSingleArgument(List *start_token, FunctionArgument *argument, char **error) {
  SyntaxNode identifire;
  List *current_token = parseIdentifier(start_token, &identifire, error);
  if (*error != NULL) {
    return current_token;
  }

  argument->name = ((SyntaxIdentifierData*) (identifire.data))->name;
  argument->token = current_token;

  current_token = trimTokensLeft(current_token);
  current_token = chopToken(current_token, TOKEN_SEPARATOR, ":", error);
  if (*error != NULL) {
    return current_token;
  }

  current_token = trimTokensLeft(current_token);

  SyntaxNode type_node;
  current_token = parseTypeDefinition(current_token, &type_node, error);
  if (*error != NULL) {
    return current_token;
  }

  argument->type_definition = *(SyntaxTypeDefinitionData*) type_node.data;

  return current_token;
}

List* trimArguments(List *start_token, Array *arguments, char **error) {
  *error = NULL;

  List *current_token = trimTokensLeft(start_token);

  current_token = chopToken(current_token, TOKEN_BRACKET_OPEN, "(", error);
  if (*error != NULL) {
    return current_token;
  }

  while (true) {
    current_token = trimTokensLeft(current_token);
    FunctionArgument argument;
    current_token = trimSingleArgument(current_token, &argument, error);
    if (*error != NULL) {
      return current_token;
    }

    arrayPush(arguments, &argument);

    current_token = trimTokensLeft(current_token);

    TokenData *token = (TokenData*) listGetValue(current_token);
    if (token->token.id != TOKEN_SEPARATOR || strcmp(token->value, ",") != 0) {
      if (token->token.id == TOKEN_BRACKET_CLOSE && strcmp(token->value, ")") == 0) {
        current_token = listNext(current_token);
        break;
      }
      *error = "Failed to parse function's arguments, unexpected token, expect ')'";
      return current_token;
    }

    current_token = listNext(current_token);
  }

  return current_token;
}

List *parseFunction(List *tokens, SyntaxNode *result, char **error) {
  *error = NULL;
  *result = (SyntaxNode) {
    .data = NULL,
    .handler = getSyntaxNodeHandler(SYNTAX_FUNCTION),
  };
  
  List *current_token = trimTokensLeft(tokens);
  result->token = current_token;

  Array *arguments = createEmptyArray(1, sizeof(FunctionArgument));
  current_token = trimArguments(current_token, arguments, error);
  if (*error != NULL) {
    arrayFree(arguments);
    return current_token;
  }

  SyntaxFunctionData *result_data = (SyntaxFunctionData*) malloc(sizeof(SyntaxFunctionData));
  result->data = result_data;

  current_token = trimTokensLeft(current_token);
  current_token = chopToken(current_token, TOKEN_SEPARATOR, ":", error);
  if (*error == NULL) {
    current_token = trimTokensLeft(current_token);

    SyntaxNode resturn_type_node;
    current_token = parseTypeDefinition(current_token, &resturn_type_node, error);
    if (*error != NULL) {
      free(result_data);
      return current_token;
    }
    result_data->return_type = *(SyntaxTypeDefinitionData*) resturn_type_node.data;
  } else {
    *error = NULL;
    result_data->return_type.type_id = SYNTAX_TYPE_ID_VOID;
  }


  result_data->arguments = arguments;

  current_token = trimTokensLeft(current_token);

  current_token = chopToken(current_token, TOKEN_FUNCTION_ARROW, NULL, error);
  if (*error != NULL) {
    free(result_data);
    return current_token;
  }

  current_token = trimTokensLeft(current_token);

  current_token = parseExpression(current_token, &(result_data->body_expression), error, NULL);
  if (*error != NULL)  {
    tokenDataPrint(listGetValue(current_token));
    free(result_data);
    return current_token;
  }

  return current_token;
}
