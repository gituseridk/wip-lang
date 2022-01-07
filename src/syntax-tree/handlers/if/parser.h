#ifndef SYNTAX_PARSER_IF_H
#define SYNTAX_PARSER_IF_H

#include "syntax-tree/syntax-node.h"

List *parseIf(List *tokens, SyntaxNode *result, char **error);

#endif
