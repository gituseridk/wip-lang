#include <stdio.h>
#include "utils/array/array.h"

int main() {
  int initialValue[] = { 0, 1, 3 };
  Array arr = newArray(3, sizeof(int), initialValue);
  printf("[%d, %d, %d]\n", *(int*)getElementAt(&arr, 0), *(int*)getElementAt(&arr, 1), *(int*)getElementAt(&arr, 2));
  return 0;
}
