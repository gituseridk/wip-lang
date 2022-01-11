#ifndef EXPRSSION_DATA_H
#define EXPRSSION_DATA_H

#include <stdbool.h>
#include <stdio.h>

#include "compiler/compile-arch.h"
#include "utils/map/map.h"
#include "utils/array/array.h"
#include "utils/list/list.h"
#include "syntax-tree/handlers/type-definition/data.h"

#define EXPRESSION_SCOPE                  1
#define EXPRESSION_ASSIGNATION            2
#define EXPRESSION_INITIALIZATION         3
#define EXPRESSION_LITERAL                4
#define EXPRESSION_FUNCTION               5
#define EXPRESSION_FUNCTION_CALL          6
#define EXPRESSION_IF                     7
#define EXPRESSION_WHILE                  8
#define EXPRESSION_RETURN                 9
#define EXPRESSION_OPERATIONS_PREFIX      10
#define EXPRESSION_OPERATIONS_POSTFIX     12
#define EXPRESSION_OPERATIONS             14

typedef struct {
  unsigned scope_offset;

  char *name;
  TypeDefinition type;
} VariableData;

typedef struct ExpressionData ExpressionData;

typedef void (*ExpressionCompile)(char *src, ExpressionData *self, FILE *out_stream);

struct ExpressionData {
  ExpressionData *parent_scope;

  Map *variables;
  Array * child_expressions;

  List *token;

  TypeDefinition result_type;

  ExpressionCompile compileX86;

  int id;
  void *value;
};

VariableData *expressionDataGetVariable(ExpressionData *self, char *name);
VariableData *getGlobalVariable(char *name);
void expressionCompile(ExpressionData *self, Architecture arch, char *src, FILE *out_stream);
void expressionInit(ExpressionData *result, int id, List *token, bool is_scope);
unsigned expressionGetSize(ExpressionData *self);

#endif
