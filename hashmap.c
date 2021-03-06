#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"

typedef struct Pair Pair;
typedef struct HashMap HashMap;
int enlarge_called=0;

struct Pair {
     char * key;
     void * value;
};

struct HashMap { // HashMap* map = (HashMap*) malloc (sizeof(HashMap));
    Pair ** buckets; // map->buckets = (Pair **) malloc (..)
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {
long x = hash(key, map->capacity);
if (map->buckets[x] != NULL){
  do {
  x++;
  if (x >= map->capacity) {
    x = 0;
  }
}while (map->buckets[x] != NULL);
}

map->buckets[x] = createPair(key, value);
map->size += 1;

}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)
/* Pair** aux = map->buckets; 
map->capacity *= 2;
map->buckets = */

}


HashMap * createMap(long capacity) {
HashMap * map = (HashMap *)malloc(sizeof(HashMap));
map->buckets = (Pair **) calloc (capacity,sizeof(Pair *));
map->current = -1;
map->capacity = capacity;
    return map;
}

void eraseMap(HashMap * map,  char * key) {    
long x = hash(key, map->capacity);
if (is_equal(key, map->buckets[x]->key) != 1) {
  do {
      x++;
      if (x >= map->capacity) {
        x = 0;
      }
    }while (map->buckets[x] != NULL && is_equal(key, map->buckets[x]->key) != 1);
  }
  if (map->buckets[x] != NULL) {
map->buckets[x]->key = NULL;
map->size -= 1;
  }
}

void * searchMap(HashMap * map,  char * key) {   
long x = hash(key, map->capacity);
map->current = x;
if (is_equal(key, map->buckets[x]->key) != 1) {
  do {
      x++;
      if (x >= map->capacity) {
        x = 0;
      }
    }while (map->buckets[x] != NULL && is_equal(key, map->buckets[x]->key) != 1);
  }
  if (map->buckets[x] == NULL) {
    return NULL;
  }
  else {
    return map->buckets[x]->value;
  }
}

void * firstMap(HashMap * map) {
  map->current = 0;
if (map->buckets[map->current] == NULL || map->buckets[map->current]->key == NULL) {
    do {
      map->current += 1;
      if (map->current == map->capacity) {
  return NULL;
}
    }while (map->buckets[map->current] ==  NULL || map->buckets[map->current]->key == NULL);
}

    return map->buckets[map->current]->value;
}

void * nextMap(HashMap * map) {
map->current += 1;
  if (map->buckets[map->current] == NULL || map->buckets[map->current]->key == NULL) {
    do {
      map->current += 1;
      if (map->current == map->capacity) {
  return NULL;
}
    }while (map->buckets[map->current] ==  NULL || map->buckets[map->current]->key == NULL);
}

return map->buckets[map->current]->value;
}
