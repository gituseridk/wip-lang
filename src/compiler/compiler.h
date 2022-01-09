#ifndef COMPILER_H
#define COMPILER_H

#include <stdio.h>

#include "expression-data/expression-data.h"

void compile(char *src, ExpressionData root_expression, FILE *out_stream);

#endif
