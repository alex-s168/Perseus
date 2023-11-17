#ifndef MAP_H
#define MAP_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifndef PASTE2
#define PASTE2(A, B) A ## B
#endif

#define Map(keyType, valType, typeName, equalsFunction) \
    typedef struct {                                    \
        keyType *keys;                                  \
        valType *values;                                \
        int size;                                       \
        int cap;                                        \
    } typeName;                                         \
                                                        \
    typeName PASTE2(typeName, Init)() {                 \
        typeName map;                                   \
        map.keys = NULL;                                \
        map.values = NULL;                              \
        map.size = 0;                                   \
        map.cap = 0;                                    \
        return map;                                     \
    }                                                   \
                                                        \
    typeName PASTE2(typeName, InitCap)(int cap) {       \
        typeName map;                                   \
        map.keys = malloc(sizeof(keyType) * cap);       \
        map.values = malloc(sizeof(valType) * cap);     \
        map.size = 0;                                   \
        map.cap = cap;                                  \
        return map;                                     \
    }                                                   \
                                                        \
    void PASTE2(typeName, Free)(typeName map) {         \
        free(map.keys);                                 \
        free(map.values);                               \
    }                                                   \
                                                        \
    void PASTE2(typeName, Clear)(typeName *map) {       \
        PASTE2(typeName, Free)(*map);                   \
        map->keys = NULL;                               \
        map->values = NULL;                             \
        map->size = 0;                                  \
        map->cap = 0;                                   \
    }                                                   \
                                                        \
    void PASTE2(typeName, Put)(typeName *map, keyType key, valType value) { \
        for (int i = 0; i < map->size; i++) {           \
            if (equalsFunction(map->keys[i], key)) {    \
                map->values[i] = value;                 \
                return;                                 \
            }                                           \
        }                                               \
                                                        \
        if (map->size == map->cap) {                    \
            map->cap = map->cap == 0 ? 1 : map->cap * 2;\
            map->keys = realloc(map->keys, sizeof(keyType) * map->cap);     \
            map->values = realloc(map->values, sizeof(valType) * map->cap); \
        }                                               \
                                                        \
        map->keys[map->size] = key;                     \
        map->values[map->size] = value;                 \
        map->size++;                                    \
    }                                                   \
                                                        \
    valType *PASTE2(typeName, Get)(typeName map, keyType key) {              \
        for (int i = 0; i < map.size; i++) {            \
            if (equalsFunction(map.keys[i], key)) {     \
                return map.values + i;                  \
            }                                           \
        }                                               \
        return NULL;                                    \
    }                                                   \
                                                        \
    valType PASTE2(typeName, GetOrPut)(typeName *map, keyType key, valType value) { \
        for (int i = 0; i < map->size; i++) {           \
            if (equalsFunction(map->keys[i], key)) {    \
                return map->values[i];                  \
            }                                           \
        }                                               \
                                                        \
        if (map->size == map->cap) {                    \
            map->cap = map->cap == 0 ? 1 : map->cap * 2;\
            map->keys = realloc(map->keys, sizeof(keyType) * map->cap);     \
            map->values = realloc(map->values, sizeof(valType) * map->cap); \
        }                                               \
                                                        \
        map->keys[map->size] = key;                     \
        map->values[map->size] = value;                 \
        map->size++;                                    \
        return value;                                   \
    }                                                   \
                                                        \
    bool PASTE2(typeName, HasKey)(typeName map, keyType key) {              \
        for (int i = 0; i < map.size; i++) {            \
            if (equalsFunction(map.keys[i], key)) {     \
                return true;                            \
            }                                           \
        }                                               \
        return false;                                   \
    }                                                   \
                                                        \
    void PASTE2(typeName, RemoveAt)(typeName *map, keyType key) {           \
        for (int i = 0; i < map->size; i++) {           \
            if (equalsFunction(map->keys[i], key)) {    \
                map->keys[i] = map->keys[map->size - 1];\
                map->values[i] = map->values[map->size - 1];                \
                map->size--;                            \
                return;                                 \
            }                                           \
        }                                               \
    }

#endif