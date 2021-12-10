#include <stdio.h>
#include <assert.h>

#include "utils/array/array.h"

void testArrays() {
  printf("Test arrays:\n");

  Array *arr = newArray(3, sizeof(int), (int[]){ 0, 1, -19 });

  printf("\t- get array elements\n");
  assert(*(int*)getElementAt(arr, 0) == 0);
  assert(*(int*)getElementAt(arr, 1) == 1);
  assert(*(int*)getElementAt(arr, 2) == -19);
  printf("\t- get length\n");
  assert(getArrayLength(arr) == 3);

  int val = 10;
  printf("\t- push element to array\n");
  push(arr, &val);

  printf("\t- check array length\n");
  assert(getArrayLength(arr) == 4);
  
  printf("\t- check if new element exists\n");
  assert(getElementAt(arr, 3) != NULL);

  printf("\t- get new element value\n");
  assert(*(int*)getElementAt(arr, 3) == val);

  printf("\t- pop element\n");
  assert(*(int*)pop(arr) == val);

  printf("\t- check array length after pop\n");
  assert(getArrayLength(arr) == 3);

  printf("\t- check if element is no longer exists in array\n");
  assert(getElementAt(arr, 3) == NULL);

  printf("\t- delete array\n");
  freeArray(arr);

  printf("Test arrays: OK\n");
}
