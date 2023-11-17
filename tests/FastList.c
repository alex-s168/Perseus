#include <stdio.h>

#include "../FastList.h"

bool intEquals(int a, int b) {
    return a == b;
}

FList(int, IntFList, intEquals);

int main() {
    IntFList list = IntFListInitCap(1000000);

    for (int i = 0; i < 1000000; i++) {
        IntFListAdd(&list, i);
    }

    IntFListRemove(&list, 50);

    // for (int i = 0; i < list.len; i++) {
    //     printf("%d ", list.data[i]);
    // }

    IntFListFree(list);

    return 0;
}