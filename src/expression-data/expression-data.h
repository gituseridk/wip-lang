#ifndef EXPRSSION_DATA_H
#define EXPRSSION_DATA_H

#include <stdbool.h>

#include "utils/map/map.h"
#include "utils/array/array.h"
#include "syntax-tree/handlers/type-definition/data.h"

#define EXPRESSION_SCOPE              1
#define EXPRESSION_ASSIGNATION        2
#define EXPRESSION_INITIALIZATION     3

typedef struct {
  unsigned scope_offset;

  char *name;
  SyntaxTypeDefinitionData result_type;
} VariableData;

typedef struct ExpressionData ExpressionData;

struct ExpressionData {
  ExpressionData *parent_scope;

  Map *variables;
  Array * child_expressions;

  SyntaxTypeDefinitionData result_type;

  int id;
};

#endif
