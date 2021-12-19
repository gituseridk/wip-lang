#ifndef SYNTAX_PARSER_SCOPE_H
#define SYNTAX_PARSER_SCOPE_H

#include "syntax-tree/syntax-node.h"

List *parseScope(List *tokens, SyntaxNode *result, char **error);

#endif
