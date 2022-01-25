#include <stdlib.h>
#include <stdio.h>

#include "utils/string/string.h"
#include "token/token-data.h"
#include "./log-src-error.h"

void printSourceError(const SourceData *src, const char *error, int row, int col) {
  printf("Error at %s:%d:%d\n", src->path, row, col);
  Array *lines = stringSplit(src->content, "\n", true);
  char **line = (char**) arrayAt(lines, row - 1);
 
  int row_num_length = 0;
  for(int i = row + 1; i != 0; i /= 10) ++row_num_length;

  if (line != NULL) {
    printf("%d | %s\n", row, *line);
  }

  for (int i = row_num_length + col; i != 0; --i) printf(" ");
  printf("  ^ %s\n", error);

  freeSplittedString(lines);
}

void throwSourceError(const char *error, List *token) {
  TokenData *token_data = (TokenData*) listGetValue(token);

  printSourceError(token_data->src, error, token_data->row, token_data->col);
  exit(1);
}
