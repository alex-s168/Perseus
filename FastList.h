#ifndef FLIST_H
#define FLIST_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifndef PASTE2
    #define PASTE2(A, B) A ## B
#endif

#define FList(type, typeName, equalsFun) \
    typedef struct { \
        size_t len;                      \
        size_t cap;                      \
        type *data;                      \
    } typeName;                          \
                                         \
    typeName PASTE2(typeName, Init)() {  \
        return (typeName) {              \
            .len = 0,                    \
            .cap = 0,                    \
            .data = NULL                 \
        };                               \
    }                                    \
                                         \
    typeName PASTE2(typeName, InitCap)(size_t cap) { \
        return (typeName) {              \
            .len = 0,                    \
            .cap = cap,                  \
            .data = malloc(cap * sizeof(type)) \
        };                               \
    }                                    \
                                         \
    void PASTE2(typeName, Free)(typeName arr) {      \
        free(arr.data);                  \
    }                                    \
                                         \
    void PASTE2(typeName, Clear)(typeName *arr) {     \
        free(arr->data);                 \
        arr->len = 0;                    \
        arr->cap = 0;                    \
    }                                    \
                                         \
    void PASTE2(typeName, ReserveExtra)(typeName *arr, size_t extra) { \
        size_t len = arr->len;           \
        if (arr->cap >= len + extra) {   \
            return;                      \
        }                                \
        arr->data = realloc(arr->data, (len + extra) * sizeof(type));  \
        arr->cap = len + extra;          \
    }                                    \
                                         \
    void PASTE2(typeName, ReduceAlloc)(typeName *arr) {                \
        size_t len = arr->len;           \
        if (len == arr->cap) {           \
            return;                      \
        }\
        arr->data = realloc(arr->data, len * sizeof(type));            \
        arr->cap = len;                  \
    }                                    \
                                         \
    void PASTE2(typeName, Add)(typeName *arr, type elem) {             \
        if (arr->cap < arr->len + 1) {   \
            arr->cap = arr->cap * 2 + 1; \
            arr->data = realloc(arr->data, arr->cap * sizeof(type));   \
        }                                \
        arr->data[arr->len++] = elem;    \
    }                                    \
                                         \
    void PASTE2(typeName, RemoveAt)(typeName *arr, unsigned int index) { \
        if (arr->len < 2) {              \
            free(arr->data);             \
            arr->len = 0;                \
            arr->cap = 0;                \
            return;                      \
        }                                \
                                         \
        memmove(arr->data + index,       \
                arr->data + index + 1,   \
                (arr->len - index) * sizeof(type));  \
                                         \
        arr->len --;                     \
                                         \
        if (arr->len < arr->cap / 2) {   \
            arr->cap = arr->cap / 2;     \
            arr->data = realloc(arr->data, arr->cap * sizeof(type)); \
        }                                \
    }                                    \
                                         \
    unsigned int PASTE2(typeName, IndexOf)(typeName arr, type elem) {\
        for (size_t i = 0; i < arr.len; i ++) {      \
            if (equalsFun(arr.data[i], elem)) {      \
                return i;                \
            }                            \
        }                                \
        return -1;                       \
    }                                    \
                                         \
    bool PASTE2(typeName, Remove)(typeName *arr, type elem) {        \
        unsigned int index = PASTE2(typeName, IndexOf)(*arr, elem);  \
        if (index == -1) {               \
            return false;                \
        }                                \
        PASTE2(typeName, RemoveAt)(arr, index);      \
        return true;                     \
     }                                   \
                                         \
    void PASTE2(typeName, AddAll)(typeName *arr, size_t otherLen, type *other) { \
        if (otherLen == 0) {             \
            return;                      \
        }                                \
        if (arr->cap < arr->len + otherLen) {        \
            arr->cap = arr->len + otherLen;          \
            arr->data = realloc(arr->data, arr->cap * sizeof(type)); \
        }                                \
        memcpy(arr->data + arr->len, other, otherLen * sizeof(type));\
        arr->len += otherLen;            \
    }                                    \
    void PASTE2(typeName, RemoveFromBegin)(typeName *arr, size_t count) { \
        if (count == 0) {                \
            return;                      \
        }                                \
        if (count >= arr->len) {         \
            PASTE2(typeName, Clear)(arr);\
            return;                      \
        }                                \
        memmove(arr->data, arr->data + count, (arr->len - count) * sizeof(type));\
        arr->len -= count;               \
        if (arr->len < arr->cap / 2) {   \
            arr->cap = arr->cap / 2;     \
            arr->data = realloc(arr->data, arr->cap * sizeof(type));   \
        }                                \
    }

#endif
