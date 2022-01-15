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
#define EXPRESSION_IDENTIFIER             4
#define EXPRESSION_LITERAL                5
#define EXPRESSION_FUNCTION               6
#define EXPRESSION_FUNCTION_CALL          7
#define EXPRESSION_IF                     8
#define EXPRESSION_WHILE                  9
#define EXPRESSION_RETURN                 10
#define EXPRESSION_OPERATIONS_PREFIX      11
#define EXPRESSION_OPERATIONS_POSTFIX     13
#define EXPRESSION_OPERATIONS             15

#define GLOBAL_VAR_NAME_PRINT_INT         "printInt"
#define GLOBAL_VAR_NAME_PRINT             "print"
#define GLOBAL_VAR_NAME_INT_TO_STR        "intToStr"
#define GLOBAL_VAR_NAME_STR_LEN           "strLen"

typedef struct ExpressionData ExpressionData;

typedef struct {
  int scope_offset;

  char *name;
  TypeDefinition type;

  ExpressionData *scope;
} VariableData;

typedef void (*ExpressionCompile)(char *src, ExpressionData *self, bool address, FILE *out_stream);

struct ExpressionData {
  const char *name;

  ExpressionData *parent_scope;

  Map *variables;
  char *scope_label;
  Array * child_expressions;

  List *token;

  TypeDefinition result_type;

  ExpressionCompile compileX86;

  int id;
  void *value;
};

VariableData *expressionDataGetVariable(ExpressionData *self, char *name, unsigned *scope_diff);
Map *getGlobalVariables(int *offset);
void expressionCompile(ExpressionData *self, Architecture arch, char *src, bool address, FILE *out_stream);
void expressionInit(ExpressionData *result, int id, const char *name, List *token, bool is_scope);
unsigned expressionGetSize(ExpressionData *self);

#endif
