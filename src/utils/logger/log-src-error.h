#ifndef LOG_SRC_ERROR_h
#define LOG_SRC_ERROR_h

#include "utils/array/array.h"

typedef struct {
  const char *text;
  int col;
  int row;
} SourceError;

void printSourceError(const char *src, const char *error, int row, int col);

#endif
