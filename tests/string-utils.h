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

  printf("\t- split string:\n");
  Array strings = splitString("123 , 345 , 567, 444", " , ");
  assert(getArrayLength(&strings) == 3);
  assert(!strcmp((char*)getElementAt(&strings, 0), "123"));
  assert(!strcmp((char*)getElementAt(&strings, 1), "345"));
  assert(!strcmp((char*)getElementAt(&strings, 2), "567, 444"));
  freeArray(&strings);

  printf("Test string utils: OK\n");
}
