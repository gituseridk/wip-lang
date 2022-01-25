#include <stdlib.h>
#include <stdio.h>

#include "utils/logger/log-src-error.h"
#include "syntax-tree/syntax-node.h"
#include "syntax-tree/syntax-helpers.h"
#include "./data.h"


void getInitializationExpressionData(
  void *raw_data,
  List *token,
  ExpressionData *result,
  int *offset,
  int handler_id
) {
  SyntaxInitializationData *data = (SyntaxInitializationData*)raw_data;

  expressionInit(result, EXPRESSION_INITIALIZATION, "initialization", token, false);
  result->compileX86 = compileInitializationX86;

  if (data->type != NULL) {
    result->result_type = *(data->type);
  } else if (result->result_type.type_id == TYPE_ID_VOID) {
    throwSourceError("missing initialization type", token);
  }

  if (mapGet(result->parent_scope->variables, data->identifier) != NULL) {
    List *identifier_token = trimTokensLeft(listNext(token));
    char msg[100];
    sprintf(msg, "name \"%s\" is already used", data->identifier);
    throwSourceError(msg, identifier_token);
  }

  result->result_type.is_constant = data->is_constant;
  VariableData *new_var = malloc(sizeof(VariableData));
  *new_var = (VariableData) {
    .scope = result->parent_scope,
    .name = data->identifier,
    .type = result->result_type,
    .scope_offset = *offset,
  };

  result->value = new_var;

  *offset += getTypeSize(&(result->result_type));

  mapSet(result->parent_scope->variables, data->identifier, new_var);
}
