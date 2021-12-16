#ifndef SYNTAX_PARSER_LITERAL_H
#define SYNTAX_PARSER_LITERAL_H

#include "syntax-tree/syntax-node.h"

List* parseLiteral(List *tokens, SyntaxNode *result, char **error);

#endif
