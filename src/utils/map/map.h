#ifndef MAP_H
#define MAP_H

// simple red-black tree

typedef char* (*ToString)(void *element);

typedef struct Map Map;

Map *createMap(int element_size);

void *mapGet(Map *self, char *key);
int mapSize(Map *self);
void mapSet(Map *self, char *key, const void *value);
void mapPrint(Map *self, ToString);

// !TODO implement
void mapPop(Map *self, char *key, void *element);

#endif
