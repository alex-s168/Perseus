#include "InstructionStream.h"

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