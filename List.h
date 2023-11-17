#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifndef PASTE2
    #define PASTE2(A, B) A ## B
#endif

#define List(type, typeName, equalsFun) \
    typedef struct { \
        size_t len; \
        type *data; \
    } typeName; \
    \
    typeName PASTE2(typeName, Init)() { \
        return (typeName) { \
            .len = 0, \
            .data = NULL \
        }; \
    } \
    \
    void PASTE2(typeName, Free)(typeName arr) { \
        free(arr.data); \
    } \
    \
    void PASTE2(typeName, Add)(typeName *arr, type elem) { \
        arr->len ++; \
        size_t len = arr->len; \
        arr->data = realloc(arr->data, len * sizeof(type)); \
        arr->data[len-1] = elem; \
    } \
    \
    void PASTE2(typeName, RemoveAt)(typeName *arr, unsigned int index) { \
        memmove(arr->data + index, \
                arr->data + index + 1, \
                (arr->len - index) * sizeof(type)); \
        arr->len --; \
        arr->data = realloc(arr->data, arr->len * sizeof(type)); \
    } \
    \
    unsigned int PASTE2(typeName, IndexOf)(typeName arr, type elem) { \
        for (size_t i = 0; i < arr.len; i ++) { \
            if (equalsFun(arr.data[i], elem)) { \
                return i; \
            } \
        } \
        return -1; \
    } \
    \
    bool PASTE2(typeName, Remove)(typeName *arr, type elem) { \
        unsigned int index = PASTE2(typeName, IndexOf)(*arr, elem); \
        if (index == -1) { \
            return false; \
        } \
        PASTE2(typeName, RemoveAt)(arr, index); \
        return true; \
     } \
     \
     void PASTE2(typeName, AddAll)(typeName *arr, size_t otherLen, type *other) { \
         size_t len = arr->len;         \
         arr->data = realloc(arr->data, (len + otherLen) * sizeof(type));\
         if (arr->data == NULL) {       \
            return;          \
         }                   \
         memcpy( arr->data + len,       \
                 other,      \
                 otherLen * sizeof(type));      \
         arr->len += otherLen;          \
     }

#endif
