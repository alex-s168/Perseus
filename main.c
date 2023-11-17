#include "Instructions.h"
#include "FastList.h"
#include "Map.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    bool isInst;
    bool isNum;
    bool isStr;
    union {
        Inst inst;
        int num;
        char *str;
    } value;
} OpPart;

#define P_INST(i) (OpPart) { .isInst = true, .value.inst = i }
#define P_NUM(i) (OpPart) { .isNum = true, .value.num = i }
#define P_STR(s) (OpPart) { .isStr = true, .value.str = s }

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

FList(OpPart, OpFList, equalsOpPart);

struct State;
typedef struct State State;

typedef void (*NativeFunction)(State *vm);

struct JITMapEntry {
    size_t callCount;

    bool isJit;
    NativeFunction jit;
};

struct Type {
    // TODO
};

typedef struct Type Type;

bool equalsType(Type a, Type b) {
    return true; // TODO
}

Map(Type, struct JITMapEntry, JITMap, equalsType);

typedef struct {
    OpFList ops;

    JITMap jitMap;
} Function;

struct State {

};

__attribute((noreturn))
void runtimeError(State *vm, char *message) {
    fprintf(stderr, "Runtime error: %s\n", message);
    exit(1);
}

typedef struct {
    Inst inst;
    OpFList args;
} InstWithArgs;

InstWithArgs consumeInst(OpFList *ops) {
    if (ops->len == 0) {
        runtimeError(NULL, "Unexpected end of block");
    }

    OpPart first = ops->data[0];
    if (!first.isInst) {
        runtimeError(NULL, "Expected instruction");
    }

    Inst inst = first.value.inst;

    size_t argCount = instArgCounts[inst];

    if (ops->len < argCount + 1) {
        runtimeError(NULL, "Unexpected end of block (missing arguments)");
    }

    OpFList args = OpFListInitCap(argCount);

    OpFListAddAll(&args, argCount, ops->data + 1);

    OpFListRemoveFromBegin(ops, argCount + 1);

    return (InstWithArgs) {
        .inst = inst,
        .args = args
    };
}

OpFList consumeBlock(OpFList *ops) {
    if (ops->len == 0) {
        runtimeError(NULL, "Unexpected end of block");
    }

    OpPart first = ops->data[0];
    if (!first.isInst || first.value.inst != OP_PUSH_LOCAL_FRAME) {
        runtimeError(NULL, "Expected block (OP_PUSH_LOCAL_FRAME)");
    }

    OpFList block = OpFListInit();

    size_t ind = 0; // indent
    for (size_t i = 1; i < ops->len; i++) {
        OpPart part = ops->data[i];

        if (part.isInst) {
            if (part.value.inst == OP_PUSH_LOCAL_FRAME) {
                ind++;
            } else if (part.value.inst == OP_POP_LOCAL_FRAME) {
                if (ind == 0) {
                    OpFListRemoveFromBegin(ops, i + 1);
                    return block;
                }
                ind--;
            }
        }

        OpFListAdd(&block, part);
    }

    runtimeError(NULL, "Unexpected end of block (missing OP_POP_LOCAL_FRAME)");
}

int main() {
    OpPart bytes[8] = (OpPart[]) {
        P_INST(OP_FUNDEF), P_STR("test"),
        P_INST(OP_PUSH_LOCAL_FRAME),
            P_INST(OP_ARGSPEC_IMM), P_NUM(1), 
            P_INST(OP_CALL), P_STR("printn"),
        P_INST(OP_POP_LOCAL_FRAME),
    };
    OpFList ops = OpFListInitCap(8);
    OpFListAddAll(&ops, 8, bytes);

    return 0;
}
