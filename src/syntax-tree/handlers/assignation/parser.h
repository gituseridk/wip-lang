#ifndef SYNTAX_PARSER_ASSIGNATION_H
#define SYNTAX_PARSER_ASSIGNATION_H

#include "syntax-tree/syntax-node.h"

List *parseAssignation(List *tokens, SyntaxNode *result, char **error);

#endif
