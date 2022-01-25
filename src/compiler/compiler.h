#ifndef COMPILER_H
#define COMPILER_H

#include <stdio.h>

#include "./compile-arch.h"
#include "expression-data/expression-data.h"

void compile(Architecture arch, ExpressionData root_expression, FILE *out_stream);

#endif
