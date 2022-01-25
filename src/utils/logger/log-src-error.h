#ifndef LOG_SRC_ERROR_h
#define LOG_SRC_ERROR_h

#include "utils/array/array.h"
#include "utils/list/list.h"
#include "token/source-data.h"

typedef struct {
  const char *text;
  int col;
  int row;
} SourceError;

void printSourceError(const SourceData *src, const char *error, int row, int col);
void throwSourceError(const char *error, List *token);

#endif
