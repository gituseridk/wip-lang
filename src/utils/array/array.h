#ifndef ARRAY_H
#define ARRAY_H

#include <stdbool.h>

typedef struct Array Array;
typedef void (*MapHandler)(void *result, void *el, int index, Array *self);
typedef void (*ForEachHandler)(void *el, int index, Array *self);

Array *createEmptyArray(unsigned reserved, unsigned el_size);
Array* createArray(unsigned length, unsigned el_size, const void *data);

void arrayFree(Array *self);

const unsigned arrayGetLength(const Array *self);

void* arrayGetElementAt(Array *self, unsigned index);
bool arraySetElementAt(Array *self, unsigned index, const void *newValue);

void* arrayPop(Array *self);
void arrayPush(Array *self, const void *element);

Array* arrayMap(Array *self, unsigned new_el_size, MapHandler handler);
void arrayForEach(Array *self, ForEachHandler handler);

#endif
