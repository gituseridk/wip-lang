#include <stdlib.h>
#include <stdio.h>

#include "utils/logger/log-src-error.h"
#include "syntax-tree/syntax-node.h"
#include "syntax-tree/syntax-helpers.h"
#include "./data.h"


void getInitializationExpressionData(
  const char *src,
  void *raw_data,
  List *token,
  ExpressionData *result,
  unsigned *offset,
  int handler_id
) {
  SyntaxInitializationData *data = (SyntaxInitializationData*)raw_data;

  expressionInit(result, EXPRESSION_INITIALIZATION, token);

  result->variables = createMap(sizeof(VariableData));
  if (data->type != NULL) {
    result->result_type = *(data->type);
  } else if (result->result_type.type_id == TYPE_ID_VOID) {
    throwSourceError(src, "missing initialization type", token);
  }

  if (mapGet(result->parent_scope->variables, data->identifier) != NULL) {
    List *identifier_token = trimTokensLeft(listNext(token));
    char msg[100];
    sprintf(msg, "name \"%s\" is already used", data->identifier);
    throwSourceError(src, msg, identifier_token);
  }

  result->result_type.is_constant = data->is_constant;
  VariableData new_var = (VariableData) {
    .name = data->identifier,
    .type = result->result_type,
    .scope_offset = *offset,
  };

  char *error = NULL;
  *offset += getTypeSize(&(result->result_type), &error);
  if (error != NULL) {
    throwSourceError(src, error, token);
  }

  mapSet(result->parent_scope->variables, data->identifier, &new_var);
}
