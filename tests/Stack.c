#include <stdio.h>

#include "../Stack.h"

Stack(int, IntStack);

int main() {
    IntStack stack = IntStackInitCap(10);

    for (int i = 0; i < 10; i++) {
        IntStackPush(&stack, i);
    }

    *IntStackPeek(&stack) = 100;

    for (int i = 0; i < 10; i++) {
        printf("%d\n", IntStackPop(&stack));
    }

    IntStackFree(stack);
}