#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include "utils/list/list.h"
#include "token/token-data.h"
#include "config/config.h"

TokenizeResult preprocessFile(Config config);

#endif
