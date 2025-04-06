#include "interp.h"
#include <stdio.h>
#include <stdlib.h>

void assert(int condition, const char *message) {
  if (!condition) {
    printf("%s\n", message);
    exit(1);
  }
}
VM *initVM() {
  VM *vm = malloc(sizeof(VM));
  vm->stackSize = 0;
  vm->firstObject = NULL;

  return vm;
}

Object *newObject(VM *vm, ObjectType type) {
  Object *object = malloc(sizeof(Object));
  object->type = type;
  object->marked = 0;

  // Insert the created object in the list of all objects:
  object->next = vm->firstObject;
  vm->firstObject = object;

  return object;
}

void pushStack(VM *vm, Object *obj) {
  assert(vm->stackSize < STACK_MAX, "Stack Overflow");
  vm->stack[vm->stackSize + 1] = obj;
  vm->stackSize += 1;
}

Object *popStack(VM *vm) {
  assert(vm->stackSize > 0, "Stack Underflow");
  vm->stackSize -= 1;
  Object *obj = vm->stack[vm->stackSize];
  return obj;
}

void pushInt(VM *vm, int value) {
  Object *object = newObject(vm, OBJ_INT);
  object->value = value;
  pushStack(vm, object);
}

Object *pushPair(VM *vm) {
  Object *object = newObject(vm, OBJ_PAIR);
  object->tail = popStack(vm);
  object->head = popStack(vm);

  pushStack(vm, object);
  return object;
}

void mark(Object *object) {
  if (object->marked)
    return;
  object->marked = 1;
  if (object->type == OBJ_PAIR) {
    mark(object->tail);
    mark(object->head);
  }
}
void markAll(VM *vm) {
  for (int i = 0; i < vm->stackSize; ++i) {
    mark(vm->stack[i]);
  }
}

void sweep(VM *vm) {
  Object **object = &vm->firstObject;

  while (*object) {
    if (!(*object)->marked) {
      // Unreachable object
      Object *unreached = *object;
      *object = unreached->next;
      free(unreached);
    } else {
      // Object is reached. Reinit marking for next GC
      (*object)->marked = 0;
      object = &(*object)->next;
    }
  }
}

void gc(VM *vm) {
  markAll(vm);
  sweep(vm);
}
