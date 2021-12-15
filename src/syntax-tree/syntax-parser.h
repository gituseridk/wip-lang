#ifndef SYNTAX_PARSER_H
#define SYNTAX_PARSER_H

#include "token/token-data.h"
#include "./syntax-node.h"

typedef struct {
  int id;
  SyntaxNode (*parseTokens)();
} SyntaxParser;

#endif
