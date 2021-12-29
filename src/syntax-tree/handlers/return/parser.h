#ifndef SYNTAX_PARSER_RETURN_H
#define SYNTAX_PARSER_RETURN_H

#include "syntax-tree/syntax-node.h"

List *parseReturn(List *start_token, SyntaxNode *result, char **error);

#endif
