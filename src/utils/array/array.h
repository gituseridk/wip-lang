#ifndef ARRAY_H
#define ARRAY_H

#include <stdbool.h>

typedef struct Array Array;

typedef void (*MapHandler)(void *self, void *result, void *el, int index, const Array *array);
typedef void (*ForEachHandler)(void *self, void *el, int index, const Array *array);
typedef bool (*FindHandler)(void *self, void *el, int index, const Array *array);
typedef bool (*CountHandler)(void *self, void *el, int index, const Array *array);
typedef bool (*FilterHandler)(void *self, void *el, int index, const Array *array);
typedef void* (*ReduceHandler)(void *self, void *acc, void *el, int index, const Array *array);

Array *createEmptyArray(unsigned reserved, unsigned el_size);
Array* createArray(unsigned length, unsigned el_size, const void *data);

#define NUMARGS(type, ...)  (sizeof((type[]){__VA_ARGS__})/sizeof(type))
#define newArray(type, ...) createArray(NUMARGS(type, __VA_ARGS__), sizeof(type), (type[]){__VA_ARGS__})

void arrayFree(Array *self);

int arrayGetLength(const Array *self);

void* arrayAt(Array *self, int index);
bool arraySetElementAt(Array *self, unsigned index, const void *newValue);

void* arrayPop(Array *self);
void arrayPush(Array *self, const void *element);

// js-like iterators
Array* arrayMap(Array *array, unsigned new_el_size, MapHandler handler, void *self);
void arrayForEach(Array *array, ForEachHandler handler, void *self);
void* arrayFind(Array *array, FindHandler handler, void *self);
int arrayCount(Array *array, CountHandler handler, void *self);
Array* arrayFilter(Array *array, FilterHandler handler, void *self);

// !TODO not impimented yet
void* arrayReduce(Array *array, ReduceHandler handler, void *self);

#endif
