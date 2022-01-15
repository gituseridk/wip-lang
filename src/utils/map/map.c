#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "utils/string/string.h"

#include "./map.h"

typedef struct MapNode MapNode;
struct MapNode {
  bool is_red;
  char *key;
  void *value;
  MapNode *parent;
  MapNode *left;
  MapNode *right;
};

struct Map {
  int size;
  int element_size;
  MapNode *root_node;
};

MapNode *createBlackNode(MapNode *parent_node) {
  MapNode *node =  malloc(sizeof(MapNode));

  node->is_red = false;
  node->key = NULL;
  node->left = NULL;
  node->right = NULL;
  node->value = NULL;
  node->parent = parent_node;

  return node;
}

Map *createMap(int element_size) {
  Map *result = malloc(sizeof(Map));

  result->size = 0;
  result->element_size = element_size;
  result->root_node = createBlackNode(NULL);

  return result;
}

static MapNode *getGrandparent(MapNode *node) {
  if (node->parent != NULL) {
    return node->parent->parent;
  }
  return NULL;
}

static MapNode *getUncle(MapNode *node) {
  MapNode *grandparent = getGrandparent(node);
  if (grandparent != NULL) {
    if (node->parent == grandparent->left) {
      return grandparent->right;
    } else {
      return grandparent->left;
    }
  }
  return NULL;
}

static void rotateLeft(Map *self, MapNode *node) {
    MapNode *pivot = node->right;
  
    pivot->parent = node->parent;
    if (node->parent != NULL) {
        if (node->parent->left == node) {
          node->parent->left = pivot;
        } else {
          node->parent->right = pivot;
        }
    } else {
      self->root_node = pivot;
    }
  
    node->right = pivot->left;
    if (node->right != NULL) {
      node->right->parent = node;
    }

    node->parent = pivot;
    pivot->left = node;
}

static void rotateRight(Map *self, MapNode *node) {
    MapNode *pivot = node->left;
  
    pivot->parent = node->parent;
    if (node->parent != NULL) {
      if (node->parent->left==node) {
        node->parent->left = pivot;
      } else {
        node->parent->right = pivot;
      }
    } else {
      self->root_node = pivot;
    }
  
    node->left = pivot->right;
    if (pivot->right != NULL) {
      pivot->right->parent = node;
    }

    node->parent = pivot;
    pivot->right = node;
}

// resturn -1 if found key eles return depth of last node
static int findNode(MapNode *start_node, MapNode **result, const char *key, int depth) {
  *result = start_node;
  if (start_node->key == NULL) {
    return depth;
  }
  int r = strcmp(key, start_node->key);
  if (r == 0) {
    return -1;
  }
  return findNode(
    r < 0 ? start_node->left : start_node->right,
    result,
    key,
    depth + 1
  );
}

static int findNodePrefix(MapNode *start_node, MapNode **result, const char *key) {
  *result = start_node;
  if (start_node->key == NULL) {
    return 0;
  }
  int r = stringComparePrefix(key, start_node->key);
  if (r == 0) {
    return strlen(start_node->key);
  }
  return findNodePrefix(
    r < 0 ? start_node->left : start_node->right,
    result,
    key
  );
}

static void setNodeValue(MapNode *node, const void *value, int element_size) {
  if (element_size == 0) {
    return;
  }
  if (node->value != NULL) {
    free(node->value);
  }
  node->value = malloc(element_size);
  memcpy(node->value, value, element_size);
}

static void insertCase1(Map *self, MapNode *node);
static void insertCase2(Map *self, MapNode *node);
static void insertCase3(Map *self, MapNode *node);
static void insertCase4(Map *self, MapNode *node);
static void insertCase5(Map *self, MapNode *node);

static void insertCase1(Map *self, MapNode *node) {
  if (node->parent == NULL) {
    node->is_red = false;
    return;
  }
  insertCase2(self, node);
}

static void insertCase2(Map *self, MapNode *node) {
  if (!node->parent->is_red) {
    return;
  }
  insertCase3(self, node);
}

static void insertCase3(Map *self, MapNode *node) {
  MapNode *u = getUncle(node);
  MapNode *g;

  if (u != NULL && u->is_red) {
    node->parent->is_red = false;
    u->is_red = false;
    g = getGrandparent(node);
    g->is_red = true;
    insertCase1(self, g);
    return;
  }
  insertCase4(self, node);
}

static void insertCase4(Map *self, MapNode *node) {
  MapNode *g = getGrandparent(node);

  if (node == node->parent->right && node->parent == g->left) {
    rotateLeft(self, node->parent);
    node = node->left;
  } else if (node == node->parent->left && node->parent == g->right) {
    rotateRight(self, node->parent);
    node = node->right;
  }
  insertCase5(self, node);
}

static void insertCase5(Map *self, MapNode *node) {
  MapNode *g = getGrandparent(node);

  node->parent->is_red = false;
  g->is_red = true;

  if (node == node->parent->left && node->parent == g->left) {
    rotateRight(self, g);
    return;
  }
  rotateLeft(self, g);
}

void mapSet(Map *self, const char *key, const void *value) {
  if (self->size == 0) {
    self->root_node->key = stringGetSubstring(key, 0, -1);
    self->root_node->value = malloc(self->element_size);
    memcpy(self->root_node->value, value, self->element_size);
    self->root_node->is_red = false;
    self->root_node->left = createBlackNode(self->root_node);
    self->root_node->right = createBlackNode(self->root_node);
    self->size = 1;
    return;
  }

  MapNode *result;
  int depth = findNode(self->root_node, &result, key, 0);
  setNodeValue(result, value, self->element_size);
  if (depth == -1) {
    return;
  }
  result->key = stringGetSubstring(key, 0, -1);
  result->is_red = true;
  result->right = createBlackNode(result);
  result->left = createBlackNode(result);

  insertCase1(self, result);

  ++(self->size);
}

void *mapGet(Map *self, const char *key) {
  MapNode *result;
  int depth = findNode(self->root_node, &result, key, 0);
  if (depth == -1) {
    return result->value;
  }
  return NULL;
}

bool mapHasKey(Map *self, const char *key) {
  MapNode *result;
  int depth = findNode(self->root_node, &result, key, 0);
  return depth == -1;
}

int mapGetFirstPrefixKeySize(Map *self, const char *key) {
  MapNode *result;
  int size = findNodePrefix(self->root_node, &result, key);
  return size;
}

int mapSize(Map *self) {
  return self->size;
}

void mapPop(Map *self, char *key, void *element) {
  printf("// !TODO 'mapPop' not implemented");
}

static void printNode(MapNode *node, ToString toString) {
  if (node->key == NULL) {
    return;
  }
  char *s = toString(node->value);
  printf("[%s]: %s\n", node->key, s);
  free(s);
  printNode(node->left, toString);
  printNode(node->right, toString);
}

void mapPrint(Map *self, ToString toString) {
  printNode(self->root_node, toString);
}


struct MapItterator {
  MapNode *current_node;
};

MapItterator *mapBegin(Map *self) {
  MapItterator *result = malloc(sizeof(MapItterator));
  if (self->root_node->key == NULL) {
    result->current_node = NULL;
    return result;
  }
  result->current_node = self->root_node;
  return result;
}

bool mapItteratorNext(MapItterator *itterator) {
  if (itterator->current_node == NULL) {
    return false;
  }
  if (itterator->current_node->left->key != NULL) {
    itterator->current_node = itterator->current_node->left;
    return true;
  }
  if (itterator->current_node->right->key != NULL) {
    itterator->current_node = itterator->current_node->right;
    return true;
  }
  while (itterator->current_node->parent != NULL) {
    if (
      itterator->current_node->parent->left == itterator->current_node &&
      itterator->current_node->parent->right->key != NULL
    ) {
      itterator->current_node = itterator->current_node->parent->right;
      return true;
    }
    itterator->current_node = itterator->current_node->parent;
  }
  itterator->current_node = NULL;
  return false;
}

bool mapItteratorIsEnded(MapItterator *itterator) {
  return itterator->current_node == NULL;
}

KVPair mapItteratorGet(MapItterator *itterator) {
  return (KVPair) {
    .value = itterator->current_node->value,
    .key = itterator->current_node->key,
  };
}
