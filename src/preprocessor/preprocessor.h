#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include "utils/list/list.h"
#include "token/token-data.h"

TokenizeResult preprocessFile(const char *path);

#endif
