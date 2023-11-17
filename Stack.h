#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifndef PASTE2
    #define PASTE2(A, B) A ## B
#endif

#define Stack(type, typeName) \
    typedef struct {          \
        size_t cap;           \
        size_t size;          \
        type *data;           \
    } typeName;               \
                              \
    typeName PASTE2(typeName, Init)() { \
        return (typeName) {   \
            .cap = 0,         \
            .size = 0,         \
            .data = NULL      \
        };                    \
    }                         \
                              \
    typeName PASTE2(typeName, InitCap)(size_t cap) { \
        return (typeName) {   \
            .cap = cap,       \
            .size = 0,         \
            .data = malloc(cap * sizeof(type)) \
        };                    \
    }                         \
                              \
    void PASTE2(typeName, Free)(typeName arr) {      \
        free(arr.data);       \
    }                         \
                              \
    void PASTE2(typeName, Clear)(typeName *arr) {    \
        free(arr->data);      \
        arr->size = 0;         \
        arr->cap = 0;         \
    }                         \
                              \
    void PASTE2(typeName, ReserveExtra)(typeName *arr, size_t extra) { \
        size_t size = arr->size; \
        if (arr->cap >= size + extra) {  \
            return;           \
        }                     \
        arr->data = realloc(arr->data, (size + extra) * sizeof(type));  \
        arr->cap = size + extra;         \
    }                         \
                              \
    void PASTE2(typeName, ReduceAlloc)(typeName *arr) {                \
        size_t size = arr->size;\
        if (size == arr->cap) {\
            return;           \
        }                     \
        arr->data = realloc(arr->data, size * sizeof(type));            \
        arr->cap = size;       \
    }                         \
                              \
    void PASTE2(typeName, Push)(typeName *arr, type val) {             \
        size_t size = arr->size;\
        if (size >= arr->cap) {\
            arr->data = realloc(arr->data, (size + 1) * sizeof(type));  \
            arr->cap = size + 1;         \
        }                     \
        arr->data[size] = val; \
        arr->size = size + 1;   \
    }                         \
                              \
    type PASTE2(typeName, Pop)(typeName *arr) {      \
        size_t size = arr->size;\
        if (size == 0) {       \
            return *(type *)0;      \
        }                     \
        arr->size = size - 1;   \
        return arr->data[size - 1];      \
    }                         \
                              \
    type *PASTE2(typeName, Peek)(typeName *arr) {    \
        size_t size = arr->size;\
        if (size == 0) {       \
            return NULL;      \
        }                     \
        return &arr->data[size - 1];     \
    }

#endif
