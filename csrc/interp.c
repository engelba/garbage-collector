#include "interp.h"
#include <stdlib.h>

VM* initVM() {
  VM *vm = malloc(sizeof(VM));
  vm->stackSize = 0;

  return vm;
}

void pushStack(VM *vm, Object obj) {

    assert(vm->stackSize < vm->STACK_MAX, "Stack Overflow" );
    vm->stack[vm->stackSize + 1] = obj;
    vm->stackSize += 1; 
}

Object popStack(VM *vm) {

    assert(vm->stackSize > 0, "Stack Underflow" );
    Object obj = vm[vm->stackSize];
    vm->stackSize -= 1;
    return obj;
}
