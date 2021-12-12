#include <stdio.h>
#include <assert.h>

#include "utils/array/array.h"
void mapHandler(void *result, void *el, int index, Array *self) {
  *(int*)result = 10000 + (*(int*)el) * 100 + index;
}

void forEachHandler(void *el, int index, Array *self) {
  assert(*(int*)el == 10000 + index);
}

void testArrays() {
  printf("Test arrays:\n");

  Array *arr = newArray(3, sizeof(int), (int[]){ 0, 1, -19 });

  printf("\t- get array elements\n");
  assert(*(int*)getElementAt(arr, 0) == 0);
  assert(*(int*)getElementAt(arr, 1) == 1);
  assert(*(int*)getElementAt(arr, 2) == -19);
  printf("\t- get length\n");
  assert(getArrayLength(arr) == 3);

  printf("\t- set array elements\n");
  int val = 999;
  assert(setElementAt(arr, 1, &val));
  printf("\t- check set element\n");
  assert(*(int*)getElementAt(arr, 1) == val);

  val = 10;
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

  printf("\t- create empty array\n");
  arr = newEmptyArray(0, sizeof(int));
  assert(arr);

  printf("\t- delete empty array\n");
  freeArray(arr);

  printf("\t- push to empty array\n");
  arr = newEmptyArray(0, sizeof(int));
  val = -69;
  push(arr, &val);
  assert((*(int*)getElementAt(arr, 0)) == -69);
  assert(getArrayLength(arr) == 1);
  freeArray(arr);

  printf("\t- map array\n");
  arr = newArray(10, sizeof(int), (int[10]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
  Array *mappedArr = arrMap(arr, sizeof(int), mapHandler);
  freeArray(arr);
  assert(getArrayLength(mappedArr) == 10);
  arrForEach(mappedArr, forEachHandler);
  freeArray(mappedArr);

  printf("Test arrays: OK\n");
}
