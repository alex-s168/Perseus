#include "../List.h"

#include <stddef.h>
#include <stdio.h>

bool intEquals(int a, int b) {
    return a == b;
}

List(int, IntList, intEquals);

int main() {
    IntList list = IntListInit();

    IntListAdd(&list, 3);
    IntListAdd(&list, 9);
    IntListAdd(&list, 5);

    IntListAddAll(&list, 4, (int []) { 1, 2, 3, 4 });

    printf("len: %zu\n", list.len);
    for (size_t i = 0; i < list.len; i ++) {
        printf("%i, ", list.data[i]);
    }

    return 0;
}

