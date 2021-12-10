#ifndef ARRAY_H
#define ARRAY_H

#include <stdbool.h>

typedef struct Array Array;
typedef void (*MapHandler)(void *result, void *el, int index, Array *self);
typedef void (*ForEachHandler)(void *el, int index, Array *self);

Array *newEmptyArray(unsigned reserved, unsigned el_size);
Array* newArray(unsigned length, unsigned el_size, const void *data);
void freeArray(Array *self);

const unsigned getArrayLength(const Array *self);

void* getElementAt(Array *self, unsigned index);
bool setElementAt(Array *self, unsigned index, const void *newValue);

void* pop(Array *self);
void push(Array *self, const void *element);

Array* arrMap(Array *self, unsigned new_el_size, MapHandler handler);
void arrForEach(Array *self, ForEachHandler handler);

#endif
