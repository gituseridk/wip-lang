#ifndef LOG_SRC_ERROR_h
#define LOG_SRC_ERROR_h

#include "utils/array/array.h"

typedef struct {
  char *text;
  int col;
  int row;
} SourceError;

void printSourceError(char *src, char *error, int row, int col);

#endif
