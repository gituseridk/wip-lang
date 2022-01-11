#ifndef MAP_H
#define MAP_H

#include <stdbool.h>

typedef struct MapItterator MapItterator;
// simple red-black tree
typedef struct Map Map;

typedef char* (*ToString)(void *element);

Map *createMap(int element_size);

void *mapGet(Map *self, const char *key);
bool mapHasKey(Map *self, const char *key);
int mapSize(Map *self);
void mapSet(Map *self, const char *key, const void *value);
void mapPrint(Map *self, ToString);

// finds the first key in the map, which is the start of the *full_key*, and returns its size
int mapGetFirstPrefixKeySize(Map *self, const char *full_key);

// !TODO implement
void mapPop(Map *self, char *key, void *element);

typedef struct
{
  char *key;
  void *value;
} KVPair;


MapItterator *mapBegin(Map *self);
bool mapItteratorNext(MapItterator *itterator);
bool mapItteratorIsEnded(MapItterator *itterator);
KVPair mapItteratorGet(MapItterator *itterator);

#endif
