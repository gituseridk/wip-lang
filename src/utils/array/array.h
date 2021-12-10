#ifndef ARRAY_H
#define ARRAY_H

typedef struct {
  unsigned el_size;
  unsigned length;
  unsigned allocated;
  void *value;
} Array;

Array newArray(unsigned length, unsigned el_size, void *data);
void freeArray(Array *self);

void* getElementAt(Array *self, unsigned index);
unsigned getArrayLength(Array *self);
void* pop(Array *self);
void push(Array *self, void *element);

#endif
