#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

typedef enum {
    OP_LOADFILE, /* args: [file path] */


    /* also identify blocks for if statements and similar */
    OP_PUSH_LOCAL_FRAME, /* args: [] */
    OP_POP_LOCAL_FRAME, /* args: [] */


    OP_CALL, /* args: [function name] */ 
    
    OP_ARGSPEC_VAR, /* args: [variable name] */
    OP_ARGSPEC_IMM, /* args: [immediate number] */
    OP_ARGSPEC_STACK, /* args: [] */
    OP_ARGSPEC_STACK_N, /* args: [amount] */

    OP_ARGGET_VAR, /* args: [variable name] */
    OP_ARGGET_STACK, /* args: [] */


    OP_STACK_PREALLOC, /* args: [amount] */

    OP_STACK_REORDER_4, /* args: [new pos of 1st elem, new pos of 2nd elem, new pos of 3rd elem, new pos of 4th elem] */
    OP_STACK_REORDER_3, /* args: [new pos of 1st elem, new pos of 2nd elem, new pos of 3rd elem] */

    OP_STACK_SWAP, /* args: [] */

    OP_STACK_PUSH_VAR, /* args: [variable name] */
    OP_STACK_PUSH_IMM, /* args: [immediate number] */
    OP_STACK_PUSH_OBJ_MEMBER_STACK, /* args: [member name] */
    OP_STACK_PUSH_OBJ_MEMBER_VAR, /* args: [member name, variable name (object)] */
    
    OP_STACK_DUP, /* args: [] */
    
    OP_STACK_POP, /* args: [] */
    OP_STACK_POP_VAR, /* args: [variable name] */
    OP_STACK_POP_OBJ_MEMBER_STACK, /* args: [member name] */
    OP_STACK_POP_OBJ_MEMBER_VAR, /* args: [member name, variable name (object)] */
   
    OP_STACK_PEEK_VAR, /* args: [variable name] */
    OP_STACK_PEEK_OBJ_MEMBER_STACK, /* args: [member name] */
    OP_STACK_PEEK_OBJ_MEMBER_VAR, /* args: [member name, variable name (object)] */


    OP_COPY_VAR_VAR, /* args: [variable name (destination), variable name (source)] */
    OP_COPY_VAR_OBJ_MEMBER_STACK, /* args: [variable name (destination), member name (source)] */
    OP_COPY_VAR_OBJ_MEMBER_VAR, /* args: [variable name (destination), member name (source), variable name (source object)] */
    OP_COPY_OBJ_MEMBER_STACK_VAR, /* args: [member name (destination), variable name (source)] */
    OP_COPY_OBJ_MEMBER_VAR_VAR, /* args: [member name (destination), variable name (destination object), variable name (destination)] */
    OP_COPY_OBJ_MEMBER_STACK_OBJ_MEMBER_STACK, /* args: [member name (destination), member name (source)], first pops the source object then the destination object */
    OP_COPY_OBJ_MEMBER_STACK_OBJ_MEMBER_VAR, /* args: [member name (destination), member name (source), variable name (source object)] */
    OP_COPY_OBJ_MEMBER_VAR_OBJ_MEMBER_STACK, /* args: [member name (destination), variable name (destination object), member name (source)] */
    OP_COPY_OBJ_MEMBER_VAR_OBJ_MEMBER_VAR, /* args: [member name (destination), variable name (destination object), member name (source), variable name (source object)] */


    OP_VARDEF_LOCAL, /* args: [variable name] */
    OP_VARDEF_GLOBAL, /* args: [variable name] */

   
    OP_ARRAY_START, /* args: [] */
    OP_ARRAY_END, /* args: [] */

    OP_ARRAY_LENGTH_STACK, /* args: [] */
    OP_ARRAY_LENGTH_VAR, /* args: [variable name] */

    OP_ARRAYCOPY_STACK_STACK_STACK, /* args: [], stack args: [destination array, source array, amount] */

    OP_REPEAT_STACK_STACK, /* args: [], stack args: [value, amount] */

    OP_ARRAYCLONE_STACK, /* args: [], stack args: [array] */
    OP_ARRAYCLONE_VAR, /* args: [variable name] */

    OP_ARRAY_GET_STACK_STACK, /* args: [], stack args: [array, index], stack returns: [element at index in array] */
    OP_ARRAY_GET_VAR_STACK, /* args: [variable name (array)], stack args: [index], stack returns: [element at index in array] */
    
    OP_ARRAY_SET_STACK_STACK_STACK, /* args: [], stack args: [array, value, index] */
    OP_ARRAY_SET_VAR_STACK_STACK, /* args: [variable name (array)], stack args: [value, index] */


    OP_OBJ_CREATE_TO_STACK, /* args: [class name] */
    OP_OBJ_CREATE_TO_VAR, /* args: [class name, variable name] */
   
    OP_OBJ_MEMBER_VAR_SET_IMM, /* args: [member name, variable name (object), immediate number] */
    OP_OBJ_MEMBER_STACK_SET_IMM, /* args: [member name, immediate number] */

    OP_OBJ_CLONE_STACK_TO_STACK, /* args: [], stack args: [object] */
    OP_OBJ_CLONE_STACK_TO_VAR, /* args: [variable name (dest)], stack args: [object] */
    OP_OBJ_CLONE_VAR_TO_STACK, /* args: [variable name (source)] */
    OP_OBJ_CLONE_VAR_TO_VAR, /* args: [variable name (source), variable name (dest) */

    
    OP_VAR_SET_IMM, /* args: [variable name, immediate number] */ 
    OP_VAR_REMOVE, /* args: [variable name] */
    

    HINT_VAR_UNUSED, /* args: [variable name] */
    HINT_FUNCTION_MANY_CALLS, /* args: [function name] */ 
    HINT_FUNCTION_MANY_CALLS_T, /* args: [function name, type] */


    OP_IF_STACK, /* args: [], takes blocks: 1 */
    OP_IF_VAR, /* args: [variable name], takes blocks: 1 */ 
    
    OP_ELSE, /* args: [], takes blocks: 1 */ 

    OP_ELSE_IF_STACK, /* args: [], takes blocks: 1 */
    OP_ELSE_IF_VAR, /* args: [variable name], takes blocks: 1 */


    OP_SWITCH_STACK, /* args: [], takes blocks: 1 */ 
    OP_SWITCH_VAR, /* args: [variable name], takes blocks: 1 */

    OP_CASE_IMMEDIATE, /* args: [immediate number], takes blocks: 1 */
    OP_CASE_VAR, /* args: [immediate number], takes blocks: 1 */
    OP_CASE_STACK, /* args: [], takes blocks: 1 */

    OP_DEFAULT, /* args: [], takes blocks: 1 */


    OP_LOOP, /* args: [], takes blocks: 1 */
    
    OP_BREAK, /* args: [], only inside of loops */

    OP_CONTINUE, /* args: [], only inside of loops */


    OP_INC_STACK, /* args: [] */
    OP_INC_VAR, /* args: [variable name] */
    OP_INC_OBJ_MEMBER_STACK, /* args: [member name] */
    OP_INC_OBJ_MEMBER_VAR, /* args: [member name, variable name (of object)] */
    
    OP_DEC_STACK, /* args: [] */
    OP_DEC_VAR, /* args: [variable name] */
    OP_DEC_OBJ_MEMBER_STACK, /* args: [member name] */
    OP_DEC_OBJ_MEMBER_VAR, /* args: [member name, variable name (of object)] */


    OP_TRY, /* args: [], takes blocks: 1 */
    OP_CATCH_VAR, /* args: [variable name (to store exception in)], takes blocks: 1 */
    OP_CATCH_STACK, /* args: [] */

    OP_THROW_STACK, /* args: [], throws an exception object located on the stack */
    OP_THROW_VAR, /* args: [variable name], throws an exception object located in the variable */

    OP_EXCEPTION_GENERATE_DEFAULT, /* args: [], pushes an default exception object onto the stack */
    OP_EXCEPTION_GENERATE_STACK, /* args: [], pushes an exception object with a message (char[]) (located on the stack) onto the stack */


    OP_CLASSDEF_START_LOCAL, /* args: [class name] */
    OP_CLASSDEF_START_GLOBAL, /* args: [class name] */

    OP_CLASSDEF_USE, /* args: [class name] */
    
    OP_CLASSDEF_VARIABLE, /* args: [name, type] */
    OP_CLASSDEF_VARIABLE_DEFAULT, /* args: [name, type], stack args: [value] */
    
    OP_CLASSDEF_STOP, /* args: [] */


    OP_FUNDEF_LOCAL, /* args: [function name], takes blocks: 1 */
    OP_FUNDEF_GLOBAL, /* args: [function name], takes blocks: 1 */


    OP_BLOCK_EXEC, /* args: [], takes blocks: 1 */
} Inst;

// first: amount of arguments
// second: amount of BLOCK arguments
// third: amount of stack arguments
int instArgCounts[][3] = (int[][3]) {
    /* [inst] = { immediate / program arguments, block arguments, stack arguments } */

    [OP_LOADFILE] = { 1, 0, 0 },

    [OP_PUSH_LOCAL_FRAME] = { 0, 0, 0 },
    [OP_POP_LOCAL_FRAME] = { 0, 0, 0 },

    [OP_CALL] = { 1, 0, 0 },

    [OP_ARGSPEC_VAR] = { 1, 0, 0 },
    [OP_ARGSPEC_IMM] = { 1, 0, 0 },
    [OP_ARGSPEC_STACK] = { 0, 0, 1 },
    [OP_ARGSPEC_STACK_N] = { 1, 0, -1 },

    [OP_ARGGET_VAR] = { 1, 0, 0 },
    [OP_ARGGET_STACK] = { 0, 0, 1 },

    [OP_STACK_PREALLOC] = { 1, 0, 0 },

    [OP_STACK_REORDER_4] = { 4, 0, 0 },
    [OP_STACK_REORDER_3] = { 3, 0, 0 },

    [OP_STACK_SWAP] = { 0, 0, 0 },

    [OP_STACK_PUSH_VAR] = { 1, 0, 0 },
    [OP_STACK_PUSH_IMM] = { 1, 0, 0 },
    [OP_STACK_PUSH_OBJ_MEMBER_STACK] = { 1, 0, 1 },
    [OP_STACK_PUSH_OBJ_MEMBER_VAR] = { 2, 0, 0 },

    [OP_STACK_DUP] = { 0, 0, 0 },

    [OP_STACK_POP] = { 0, 0, 0 },
    [OP_STACK_POP_VAR] = { 1, 0, 0 },
    [OP_STACK_POP_OBJ_MEMBER_STACK] = { 1, 0, 1 },
    [OP_STACK_POP_OBJ_MEMBER_VAR] = { 2, 0, 0 },

    [OP_STACK_PEEK_VAR] = { 1, 0, 0 },
    [OP_STACK_PEEK_OBJ_MEMBER_STACK] = { 1, 0, 1 },
    [OP_STACK_PEEK_OBJ_MEMBER_VAR] = { 2, 0, 0 },

    [OP_COPY_VAR_VAR] = { 2, 0, 0 },
    [OP_COPY_VAR_OBJ_MEMBER_STACK] = { 2, 0, 1 },
    [OP_COPY_VAR_OBJ_MEMBER_VAR] = { 3, 0, 0 },
    [OP_COPY_OBJ_MEMBER_STACK_VAR] = { 2, 0, 0 },
    [OP_COPY_OBJ_MEMBER_VAR_VAR] = { 3, 0, 0 },
    [OP_COPY_OBJ_MEMBER_STACK_OBJ_MEMBER_STACK] = { 2, 0, 2 },
    [OP_COPY_OBJ_MEMBER_STACK_OBJ_MEMBER_VAR] = { 3, 0, 1 },
    [OP_COPY_OBJ_MEMBER_VAR_OBJ_MEMBER_STACK] = { 3, 0, 1 },
    [OP_COPY_OBJ_MEMBER_VAR_OBJ_MEMBER_VAR] = { 4, 0, 0 },

    [OP_VARDEF_LOCAL] = { 1, 0, 0 },
    [OP_VARDEF_GLOBAL] = { 1, 0, 0 },

    [OP_ARRAY_START] = { 0, 0, 0 },
    [OP_ARRAY_END] = { 0, 0, 0 },

    [OP_ARRAY_LENGTH_STACK] = { 0, 0, 1 },
    [OP_ARRAY_LENGTH_VAR] = { 1, 0, 0 },

    [OP_ARRAYCOPY_STACK_STACK_STACK] = { 0, 0, 3 },

    [OP_REPEAT_STACK_STACK] = { 0, 0, 2 },

    [OP_ARRAYCLONE_STACK] = { 0, 0, 1 },
    [OP_ARRAYCLONE_VAR] = { 1, 0, 0 },

    [OP_ARRAY_GET_STACK_STACK] = { 0, 0, 2 },
    [OP_ARRAY_GET_VAR_STACK] = { 1, 0, 1 },

    [OP_ARRAY_SET_STACK_STACK_STACK] = { 0, 0, 3 },
    [OP_ARRAY_SET_VAR_STACK_STACK] = { 1, 0, 2 },

    [OP_OBJ_CREATE_TO_STACK] = { 1, 0, 0 },
    [OP_OBJ_CREATE_TO_VAR] = { 2, 0, 0 },

    [OP_OBJ_MEMBER_VAR_SET_IMM] = { 3, 0, 0 },
    [OP_OBJ_MEMBER_STACK_SET_IMM] = { 2, 0, 1 },

    [OP_OBJ_CLONE_STACK_TO_STACK] = { 0, 0, 1 },
    [OP_OBJ_CLONE_STACK_TO_VAR] = { 1, 0, 1 },
    [OP_OBJ_CLONE_VAR_TO_STACK] = { 1, 0, 0 },
    [OP_OBJ_CLONE_VAR_TO_VAR] = { 2, 0, 0 },

    [OP_VAR_SET_IMM] = { 2, 0, 0 },
    [OP_VAR_REMOVE] = { 1, 0, 0 },

    [HINT_VAR_UNUSED] = { 1, 0, 0 },
    [HINT_FUNCTION_MANY_CALLS] = { 1, 0, 0 },
    [HINT_FUNCTION_MANY_CALLS_T] = { 2, 0, 0 },

    [OP_IF_STACK] = { 0, 1, 0 },
    [OP_IF_VAR] = { 1, 1, 0 },

    [OP_ELSE] = { 0, 1, 0 },

    [OP_ELSE_IF_STACK] = { 0, 1, 0 },
    [OP_ELSE_IF_VAR] = { 1, 1, 0 },

    [OP_SWITCH_STACK] = { 0, 1, 0 },
    [OP_SWITCH_VAR] = { 1, 1, 0 },

    [OP_CASE_IMMEDIATE] = { 1, 1, 0 },
    [OP_CASE_VAR] = { 1, 1, 0 },
    [OP_CASE_STACK] = { 0, 1, 0 },

    [OP_DEFAULT] = { 0, 1, 0 },

    [OP_LOOP] = { 0, 1, 0 },

    [OP_BREAK] = { 0, 0, 0 },

    [OP_CONTINUE] = { 0, 0, 0 },

    [OP_TRY] = { 0, 1, 0 },
    [OP_CATCH_VAR] = { 1, 1, 0 },
    [OP_CATCH_STACK] = { 0, 1, 0 },

    [OP_THROW_STACK] = { 0, 0, 1 },
    [OP_THROW_VAR] = { 1, 0, 0 },

    [OP_EXCEPTION_GENERATE_DEFAULT] = { 0, 0, 0 },
    [OP_EXCEPTION_GENERATE_STACK] = { 0, 0, 1 },

    [OP_CLASSDEF_START_LOCAL] = { 1, 0, 0 },
    [OP_CLASSDEF_START_GLOBAL] = { 1, 0, 0 },

    [OP_CLASSDEF_USE] = { 1, 0, 0 },

    [OP_CLASSDEF_VARIABLE] = { 2, 0, 0 },
    [OP_CLASSDEF_VARIABLE_DEFAULT] = { 2, 0, 1 },

    [OP_CLASSDEF_STOP] = { 0, 0, 0 },

    [OP_FUNDEF_LOCAL] = { 1, 1, 0 },
    [OP_FUNDEF_GLOBAL] = { 1, 1, 0 },

    [OP_BLOCK_EXEC] = { 0, 1, 0 },
};
#endif
