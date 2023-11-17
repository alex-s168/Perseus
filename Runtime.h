#ifndef PERSEUS_RUNTIME_H
#define PERSEUS_RUNTIME_H

#include "Instructions.h"
#include "FastList.h"
#include "Map.h"
#include "Stack.h"

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

bool equalsOpPart(OpPart a, OpPart b);
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
    // TODO (numbers, arrays, classes)
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

typedef struct {
    // TODO
} Object;

bool equalsString(char *a, char *b) {
    return !strcmp(a, b);
}

Map(char *, Object, VariablesMap, equalsString);
Map(char *, Function, FunctionMap, equalsString);

typedef struct {
    VariablesMap variables;
    FunctionMap functions;
} LocalFrame;

LocalFrame LocalFrameInit();
void LocalFrameFree(LocalFrame frame);

Stack(LocalFrame, LocalFrameStack);

struct State {
    VariablesMap globalVars;
    FunctionMap globalFuncs;

    LocalFrameStack localFrames;
};

State StateInit();
void StateFree(State vm);

typedef struct {
    Inst inst;
    OpFList args;
} InstWithArgs;

__attribute((noreturn))
void runtimeError(State *vm, char *message);

#include "InstructionStream.h"

#endif //PERSEUS_RUNTIME_H
