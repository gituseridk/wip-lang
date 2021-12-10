#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "utils/string/string.h"

void testStringUtils() {
  printf("Test string utils:\n");

  printf("\t- get substring:\n");
  char *sub_string = getSubstring("kek lol chebureck", 4, 10);
  assert(!strcmp(sub_string, "lol che"));
  free(sub_string);

  printf("\t- get reversed substring:\n");
  sub_string = getSubstring("kek lol chebureck", 10, 4);
  free(sub_string);

  printf("\t- reverse string:\n");
  sub_string = getSubstring("kek lol chebureck", -1, 0);
  assert(!strcmp(sub_string, "kcerubehc lol kek"));
  free(sub_string);

  printf("Test string utils: OK\n");
}
