#include <stdio.h>
#include <assert.h>

#include "utils/array/array.h"

void mapHandler(void *self, void *result, const void *el, int index, const Array *array) {
  *(int*)result = 10000 + (*(int*)el) * 100 + index;
}

void forEachHandler(void *self, const void *el, int index, const Array *array) {
  assert(*(int*)el == 10000 + index);
}

bool filterNegative(void *self, const void *el, int index, const Array *array) {
  return *(int*)el < 0;
}

bool findRound(void *self, const void *el, int index, const Array *array) {
  int val = *(int*)el;
  return (val % 100 == 0 ) && (val != 0);
}

void testArrays() {
  printf("Test arrays:\n");

  Array *arr = createArray(3, sizeof(int), (int[]){ 0, 1, -19 });

  printf("\t- get array elements\n");
  assert(*(int*)arrayGetElementAt(arr, 0) == 0);
  assert(*(int*)arrayGetElementAt(arr, 1) == 1);
  assert(*(int*)arrayGetElementAt(arr, 2) == -19);
  printf("\t- get length\n");
  assert(arrayGetLength(arr) == 3);

  printf("\t- set array elements\n");
  int val = 999;
  assert(arraySetElementAt(arr, 1, &val));
  printf("\t- check set element\n");
  assert(*(int*)arrayGetElementAt(arr, 1) == val);

  val = 10;
  printf("\t- push element to array\n");
  arrayPush(arr, &val);

  printf("\t- check array length\n");
  assert(arrayGetLength(arr) == 4);
  
  printf("\t- check if new element exists\n");
  assert(arrayGetElementAt(arr, 3) != NULL);

  printf("\t- get new element value\n");
  assert(*(int*)arrayGetElementAt(arr, 3) == val);

  printf("\t- pop element\n");
  assert(*(int*)arrayPop(arr) == val);

  printf("\t- check array length after pop\n");
  assert(arrayGetLength(arr) == 3);

  printf("\t- check if element is no longer exists in array\n");
  assert(arrayGetElementAt(arr, 3) == NULL);

  printf("\t- delete array\n");
  arrayFree(arr);

  printf("\t- create empty array\n");
  arr = createEmptyArray(0, sizeof(int));
  assert(arr);

  printf("\t- delete empty array\n");
  arrayFree(arr);

  printf("\t- push to empty array\n");
  arr = createEmptyArray(0, sizeof(int));
  val = -69;
  arrayPush(arr, &val);
  assert((*(int*)arrayGetElementAt(arr, 0)) == -69);
  assert(arrayGetLength(arr) == 1);
  arrayFree(arr);

  printf("\t- map array\n");
  arr = newArray(int, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  Array *mappedArr = arrayMap(arr, sizeof(int), mapHandler, NULL);
  arrayFree(arr);
  assert(arrayGetLength(mappedArr) == 10);
  arrayForEach(mappedArr, forEachHandler, NULL);
  arrayFree(mappedArr);


  arr = newArray(int, 196, -3, 22, 4, 0, 7, 6, 10000, -245);

  printf("\t- filter array\n");
  Array *filteredArray = arrayFilter(arr, filterNegative, NULL);
  assert(arrayGetLength(filteredArray) == 2);
  assert(*(int*)arrayGetElementAt(filteredArray, 0) == -3);
  assert(*(int*)arrayGetElementAt(filteredArray, 1) == -245);
  arrayFree(filteredArray);

  printf("\t- find\n");
  assert(*(int*)arrayFind(arr, findRound, NULL) == 10000);

  printf("\t- count negative\n");
  assert(arrayCount(arr, filterNegative, NULL) == 2);

  arrayFree(arr);

  printf("Test arrays: OK\n");
}
