#ifndef X86_COMPILE_H
#define X86_COMPILE_H

#include <stdio.h>
#include "expression-data/expression-data.h"

void compileX86(ExpressionData root_expression, FILE *out_stream);

#endif
