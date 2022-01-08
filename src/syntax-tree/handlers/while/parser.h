#ifndef SYNTAX_PARSER_WHILE_H
#define SYNTAX_PARSER_WHILE_H

#include "syntax-tree/syntax-node.h"

List *parseWhile(List *tokens, SyntaxNode *result, char **error);

#endif
