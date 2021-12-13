#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "./array.h"

#define ALLOC_MULT 2

struct Array {
  unsigned el_size;
  unsigned length;
  unsigned allocated;
  void *value;
};

Array *createEmptyArray(unsigned reserved, unsigned el_size) {
  void *value = malloc(el_size * reserved);

  Array *result = malloc(sizeof(struct Array));
  result->el_size = el_size;
  result->length = 0;
  result->allocated = reserved;
  result->value = value;

  return result;
}

Array* createArray(unsigned length, unsigned el_size, const void *data) {
  unsigned dataSize = el_size * length;
  void *value = malloc(el_size * length);
  memcpy(value, data, dataSize);

  Array *result = malloc(sizeof(struct Array));
  result->el_size = el_size;
  result->length = length;
  result->allocated = length;
  result->value = value;

  return result;
}
void arrayFree(Array *self) {
  self->allocated = 0;
  self->length = 0;
  free(self->value);
  free(self);
}

void* arrayGetElementAt(Array *self, unsigned index) {
  if (index >= self->length) {
    return NULL;
  }
  return self->value + (self->el_size * index);
}

bool arraySetElementAt(Array *self, unsigned index, const void *newValue) {
  if (index >= self->length) {
    return false;
  }
  memcpy(self->value + index * self->el_size, newValue, self->el_size);
  return true;
}

const unsigned arrayGetLength(const Array *self) {
  return self->length;
}

// !TODO free mem when more than half is unused
void* arrayPop(Array *self) {
  if (self->length == 0) {
    return NULL;
  }
  --self->length;
  return self->value + (self->el_size * self->length);
}

void arrayPush(Array *self, const void *element) {
  if (self->length < self->allocated) {
    memcpy(self->value + (self->length * self->el_size), element, self->el_size);
    ++self->length;
    return;
  }
  self->value = realloc(self->value, self->el_size * self->length * ALLOC_MULT);
  memcpy(self->value + self->length * self->el_size, element, self->el_size);
  self->allocated = self->length * ALLOC_MULT;
  ++self->length;
}

Array* arrayMap(Array *self, unsigned new_el_size, MapHandler handler) {
  Array *result = createEmptyArray(self->length, new_el_size);
  result->length = self->length;
  for (int i = 0; i != self->length; ++i) {
    handler(result->value + i * new_el_size, arrayGetElementAt(self, i), i, self);
  }
  return result;
}

void arrayForEach(Array *self, ForEachHandler handler) {
  for (int i = 0; i != self->length; ++i) {
    handler(arrayGetElementAt(self, i), i, self);
  }
}

Array* arrayFilter(Array *self, FilterHandler handler) {
  Array *result = createEmptyArray(0, self->el_size);
  for (int i = 0; i != self->length; ++i) {
    void *el = arrayGetElementAt(self, i);
    if (handler(el, i, self)) {
      arrayPush(result, el);
    }
  }
  return result;
}

void* arrayFind(Array *self, FindHandler handler) {
  for (int i = 0; i != self->length; ++i) {
    void *el = arrayGetElementAt(self, i);
    if (handler(el, i, self)) {
      return el;
    }
  }
  return NULL;
}
