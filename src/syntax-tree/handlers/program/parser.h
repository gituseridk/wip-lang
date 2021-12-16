#ifndef SYNTAX_PARSER_PROGRAM_H
#define SYNTAX_PARSER_PROGRAM_H

#include "syntax-tree/syntax-node.h"

List *parseProgram(List *tokens, SyntaxNode *result, char **error);

#endif
