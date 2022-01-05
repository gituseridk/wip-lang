#include <stdlib.h>
#include <stdio.h>

#include "utils/string/string.h"
#include "token/token-data.h"
#include "./log-src-error.h"

#define RANGE 4

static void printLine(void *_self, void *line, int index, const Array *array) {
  SourceError err = *(SourceError*) _self;
  int row = err.row;
  int col = err.col;
  if (index + 1 < row - RANGE || index + 1 > row + RANGE) {
    return;
  }

  int max_row_num_length = 0;
  for(int i = arrayGetLength(array) + 1; i != 0; i /= 10) ++max_row_num_length;
  int row_num_length = 0;
  for(int i = index + 1; i != 0; i /= 10) ++row_num_length;

  for (int i = max_row_num_length - row_num_length; i != 0; --i) printf(" ");

  printf("%d | %s\n", index + 1, *(char**) line);
  if (index + 1 == row) {
    for(int i = col + max_row_num_length; i != 0; --i) {
      printf(" ");
    }
    printf("  ^ %s\n", err.text);
  }
}

void printSourceError(const char *src, const char *error, int row, int col) {
  printf("Error at %d:%d\n", row, col);
  Array *lines = stringSplit(src, "\n", true);
  SourceError err = (SourceError) {
    .text = error,
    .col = col,
    .row = row,
  };
  arrayForEach(lines, printLine, &err);
  freeSplittedString(lines);
}

void throwSourceError(const char *src, const char *error, List *token) {
  TokenData *token_data = (TokenData*) listGetValue(token);

  printSourceError(src, error, token_data->row, token_data->col);
  exit(1);
}
