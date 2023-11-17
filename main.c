#include "Runtime.h"

#include <stdbool.h>

#define P_INST(i) (OpPart) { .isInst = true, .value.inst = i }
#define P_NUM(i) (OpPart) { .isNum = true, .value.num = i }
#define P_STR(s) (OpPart) { .isStr = true, .value.str = s }

int main() {
    OpPart bytes[8] = (OpPart[]) {
        P_INST(OP_FUNDEF_GLOBAL), P_STR("test"),
        P_INST(OP_PUSH_LOCAL_FRAME),
            P_INST(OP_ARGSPEC_IMM), P_NUM(1), 
            P_INST(OP_CALL), P_STR("printn"),
        P_INST(OP_POP_LOCAL_FRAME),
    };
    OpFList ops = OpFListInitCap(8);
    OpFListAddAll(&ops, 8, bytes);

    return 0;
}
