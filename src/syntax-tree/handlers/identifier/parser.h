#ifndef SYNTAX_PARSER_IDENTIFIER_H
#define SYNTAX_PARSER_IDENTIFIER_H

#include "syntax-tree/syntax-node.h"

List* parseIdentifier(List *tokens, SyntaxNode *result, char **error);

#endif
