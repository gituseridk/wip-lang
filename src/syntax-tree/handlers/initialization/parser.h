#ifndef SYNTAX_PARSER_INITIALIZATION_H
#define SYNTAX_PARSER_INITIALIZATION_H

#include "syntax-tree/syntax-node.h"

List *parseInitialization(List *tokens, SyntaxNode *result, char **error);

#endif
