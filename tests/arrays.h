#include <stdio.h>
#include <assert.h>

#include "utils/array/array.h"

void mapHandler(void *result, const void *el, int index, const Array *self) {
  *(int*)result = 10000 + (*(int*)el) * 100 + index;
}

void forEachHandler(const void *el, int index, const Array *self) {
  assert(*(int*)el == 10000 + index);
}

bool filterNegative(const void *el, int index, const Array *self) {
  return *(int*)el < 0;
}

bool findRound(const void *el, int index, const Array *self) {
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
  Array *mappedArr = arrayMap(arr, sizeof(int), mapHandler);
  arrayFree(arr);
  assert(arrayGetLength(mappedArr) == 10);
  arrayForEach(mappedArr, forEachHandler);
  arrayFree(mappedArr);


  arr = newArray(int, 196, -3, 22, 4, 0, 7, 6, 10000, -245);

  printf("\t- filter array\n");
  Array *filteredArray = arrayFilter(arr, filterNegative);
  assert(arrayGetLength(filteredArray) == 2);
  assert(*(int*)arrayGetElementAt(filteredArray, 0) == -3);
  assert(*(int*)arrayGetElementAt(filteredArray, 1) == -245);
  arrayFree(filteredArray);

  printf("\t- find\n");
  assert( *(int*)arrayFind(arr, findRound) == 10000);

  arrayFree(arr);

  printf("Test arrays: OK\n");
}
