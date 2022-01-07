#include <stdlib.h>
#include <stdio.h>

#include "utils/array/array.h"
#include "syntax-tree/handlers/expression/parser.h"
#include "syntax-tree/syntax-helpers.h"

#include "./parser.h"
#include "./data.h"

List* parseLiteral(List *token, SyntaxNode *result, char **error) {
  *error = NULL;
  *result = (SyntaxNode) {
    .data = NULL,
    .handler = getSyntaxNodeHandler(SYNTAX_LITERAL), 
  };
  result->token = token;

  TokenData *token_data = listGetValue(token);
  
  bool is_negative = false;

  if (token_data->token.id == TOKEN_OPERATOR_SUM || token_data->token.id == TOKEN_OPERATOR_DIFFERENCE) {
    is_negative = token_data->token.id == TOKEN_OPERATOR_DIFFERENCE;
    token = trimTokensLeft(listNext(token));
    token_data = listGetValue(token);

    if (token_data->token.id != TOKEN_LITERAL_FLOAT && token_data->token.id != TOKEN_LITERAL_INT) {
      *error = "unexpected literal type, expect int or float";
      return token;
    }
  }

  if (token_data->token.id == TOKEN_LITERAL_FLOAT) {
    SyntaxLiteralData *data = malloc(sizeof(SyntaxLiteralData));
    data->type_definition.type_id = SYNTAX_TYPE_ID_FLOAT;
    data->value = malloc(sizeof(float));
    (*(float*) data->value) = atof(token_data->value) * (is_negative ? -1 : 1);
    result->data = data;
    return listNext(token);
  }
  if (token_data->token.id == TOKEN_LITERAL_INT) {
    SyntaxLiteralData *data = malloc(sizeof(SyntaxLiteralData));
    data->type_definition.type_id = SYNTAX_TYPE_ID_INT;
    data->value = malloc(sizeof(int));
    (*(int*) data->value) = atoi(token_data->value) * (is_negative ? -1 : 1);
    result->data = data;
    return listNext(token);
  }
  if (token_data->token.id == TOKEN_LITERAL_STRING) {
    *error = "Strings is not supported yet";
    return token;
  }

  *error = "Token is not a literal";

  return token;
}
