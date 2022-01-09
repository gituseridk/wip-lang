#ifndef SYNTAX_DATA_FUNCTION_H
#define SYNTAX_DATA_FUNCTION_H

#include "syntax-tree/syntax-node.h"
#include "syntax-tree/handlers/type-definition/data.h"
#include "syntax-tree/handlers/scope/data.h"

typedef struct {
  Array *args; // array of VariableData
  TypeDefinition result_type;
} FunctionTypeData;

typedef struct {
  List *token;
  char *name;
  TypeDefinition type_definition;
} FunctionArgument;

typedef struct {
  Array *arguments;
  TypeDefinition return_type;
  SyntaxNode body_expression;
} SyntaxFunctionData;

void printSyntaxFunctionData(SyntaxFunctionData *data);

void getFunctionExpressionData(
  const char *src,
  void *raw_data,
  List *token,
  ExpressionData *result,
  unsigned *offset,
  int handler_id
);

#endif
