#include "Runtime.h"

__attribute((noreturn))
void runtimeError(State *vm, char *message) {
    fprintf(stderr, "Runtime error: %s\n", message);
    exit(1);
}

bool equalsOpPart(OpPart a, OpPart b) {
    if (a.isInst && b.isInst) {
        return a.value.inst == b.value.inst;
    } else if (a.isNum && b.isNum) {
        return a.value.num == b.value.num;
    } else if (a.isStr && b.isStr) {
        return strcmp(a.value.str, b.value.str) == 0;
    }
    return false;
}

LocalFrame LocalFrameInit() {
    return (LocalFrame) {
            .variables = VariablesMapInit(),
            .functions = FunctionMapInit(),
    };
}

void LocalFrameFree(LocalFrame frame) {
    VariablesMapFree(frame.variables);
    FunctionMapFree(frame.functions);
}

State StateInit() {
    return (State) {
            .globalVars = VariablesMapInit(),
            .globalFuncs = FunctionMapInit(),
            .localFrames = LocalFrameStackInit(),
    };
}

void StateFree(State vm) {
    VariablesMapFree(vm.globalVars);
    FunctionMapFree(vm.globalFuncs);
    LocalFrameStackFree(vm.localFrames);
}