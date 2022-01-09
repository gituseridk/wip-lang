#ifndef EXPRSSION_DATA_H
#define EXPRSSION_DATA_H

#include <stdbool.h>

#include "utils/map/map.h"
#include "utils/array/array.h"
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
  TypeDefinition result_type;

  bool is_constant;
} VariableData;

typedef struct ExpressionData ExpressionData;

struct ExpressionData {
  ExpressionData *parent_scope;

  Map *variables;
  Array * child_expressions;

  TypeDefinition result_type;

  int id;
  void *value;
};

VariableData *expressionDataGetVariable(ExpressionData *self, char *name);

#endif
