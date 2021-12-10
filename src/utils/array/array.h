#ifndef ARRAY_H
#define ARRAY_H

typedef struct {
  unsigned el_size;
  unsigned length;
  unsigned allocated;
  void *value;
} Array;

const Array newArray(unsigned length, unsigned el_size, const void *data);
void freeArray(Array *self);

void* getElementAt(Array *self, unsigned index);
const unsigned getArrayLength(const Array *self);
void* pop(Array *self);
void push(Array *self, void *element);

#endif
