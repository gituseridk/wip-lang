#ifndef ARRAY_H
#define ARRAY_H

#include <stdbool.h>

typedef struct Array Array;

typedef void (*MapHandler)(void *result, const void *el, int index, const Array *self);
typedef void (*ForEachHandler)(const void *el, int index, const Array *self);
typedef bool (*FindHandler)(const void *el, int index, const Array *self);
typedef bool (*CountHandler)(const void *el, int index, const Array *self);
typedef bool (*FilterHandler)(const void *el, int index, const Array *self);
typedef void* (*ReduceHandler)(void *acc, const void *el, int index, const Array *self);

Array *createEmptyArray(unsigned reserved, unsigned el_size);
Array* createArray(unsigned length, unsigned el_size, const void *data);

#define NUMARGS(type, ...)  (sizeof((type[]){__VA_ARGS__})/sizeof(type))
#define newArray(type, ...) createArray(NUMARGS(type, __VA_ARGS__), sizeof(type), (type[]){__VA_ARGS__})

void arrayFree(Array *self);

const unsigned arrayGetLength(const Array *self);

void* arrayGetElementAt(Array *self, unsigned index);
bool arraySetElementAt(Array *self, unsigned index, const void *newValue);

void* arrayPop(Array *self);
void arrayPush(Array *self, const void *element);

// js-like iterators
Array* arrayMap(Array *self, unsigned new_el_size, MapHandler handler);
void arrayForEach(Array *self, ForEachHandler handler);
void* arrayFind(Array *self, FindHandler handler);
int arrayCount(Array *self, CountHandler handler);
Array* arrayFilter(Array *self, FilterHandler handler);

// !TODO not impimented yet
void* arrayReduce(Array *self, ReduceHandler handler);

#endif
