#include <stdio.h>

#include "../Map.h"

bool intEquals(int a, int b) {
    return a == b;
}

Map(int, char *, TestMap, intEquals);

int main() {
    TestMap map = TestMapInit();

    TestMapPut(&map, 1, "one");
    TestMapPut(&map, 2, "two");
    TestMapPut(&map, 3, "three");
    TestMapPut(&map, 4, "four");

    TestMapPut(&map, 1, "not one");

    for (size_t i = 1; i < 10; i++) {
        char **value = TestMapGet(map, i);
        if (value == NULL) {
            printf("%zu: ?\n", i);
            continue;
        }

        printf("%zu: %s\n", i, *value);
    }

    TestMapClear(&map);

    return 0;
}