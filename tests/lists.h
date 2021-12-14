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

  val = -2;
  printf("\t- push element\n");
  List *newEl = listPushAfter(list, &val, sizeof(int));
  assert(*(int*)listGetValue(newEl) == -2);
  assert(*(int*)listGetValue(listFindBegin(newEl)) == 123);

  printf("\t- free list\n");
  listFree(newEl);

  list = NULL;
  val = 420;
  printf("\t- create list with listPushAfter\n");
  list = listPushAfter(list, &val, sizeof(int));

  printf("Test lists: OK\n");
}
