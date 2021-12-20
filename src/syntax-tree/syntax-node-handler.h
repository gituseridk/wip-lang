#ifndef SYNTAX_NODE_HANDLER_H
#define SYNTAX_NODE_HANDLER_H

#include "utils/array/array.h"

#define SYNTAX_SCOPE 0
#define SYNTAX_ASSIGNATION 1
#define SYNTAX_OPERATION_LR 2
#define SYNTAX_INITIALIZATION 3
#define SYNTAX_LITERAL 4
#define SYNTAX_IDENTIFIER 5

typedef void (*PrintData)(void *data);

typedef struct {
  int id;
  char *name;
  PrintData printData;
} SyntaxNodeHandler;

SyntaxNodeHandler *getSyntaxNodeHandler(int id);

#endif
