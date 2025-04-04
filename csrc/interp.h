// This is a dummy interpreter for a dynamically typed language with two types:
// int and pairs

#ifndef INTERP_H
#define INTERP_H

#define STACK_MAX 256

// Define the two possibles types
typedef enum { OBJ_INT, OBJ_PAIR } ObjectType;

// Define an object that can either be a int or a pair
typedef struct sObject {
  ObjectType type;

  union {
    /* OBJ_INT */
    int value;

    struct {
      struct sObject *head;
      struct sObject *tail;
    };
  };
} Object;

// Define the Virtual Machine (VM) struct
typedef struct {
  Object *stack[STACK_MAX]; // Define our stack of Objects
  int stackSize = 0;
} VM;

// Function that initialize a VM
VM *initVM();

// Stack Manipulation
void pushStack(VM *vm, Object obj);
Object popStack(VM *vm);

#endif
