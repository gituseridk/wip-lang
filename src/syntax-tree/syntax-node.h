#ifndef SYNTAX_NODE_H
#define SYNTAX_NODE_H

#include "syntax-node-handler.h"
#include "token/token-data.h"

#define SYNTAX_TYPE_ID_VOID       0
#define SYNTAX_TYPE_VOID_NAME     "void"

#define SYNTAX_TYPE_ID_POINTER    1
#define SYNTAX_TYPE_POINTER_NAME  "pointer"

#define SYNTAX_TYPE_ID_STRUCT     2
#define SYNTAX_TYPE_STRUCT_NAME   "struct"

#define SYNTAX_TYPE_ID_INT        3
#define SYNTAX_TYPE_INT_NAME      "int"

#define SYNTAX_TYPE_ID_FLOAT      4
#define SYNTAX_TYPE_FLOAT_NAME    "float"

#define SYNTAX_TYPE_ID_CHAR       5
#define SYNTAX_TYPE_CHAR_NAME     "char"

typedef struct SyntaxNode SyntaxNode;

struct SyntaxNode {
  SyntaxNodeHandler *handler;
  void *data;
};

void syntaxNodePrint(SyntaxNode *self);

#endif
