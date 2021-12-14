#include <stdio.h>
#include <assert.h>

#include "utils/list/list.h"

// !TODO add more tests
void testLists() {
  printf("Test lists:\n");

  printf("\t- create list\n");
  int val = 123;
  List *list = createList(&val, sizeof(int));

  printf("\t- check created list\n");
  assert(list != NULL);

  printf("\t- get value\n");
  assert(*(int*)listGetValue(list) == 123);
}
