// This is a dummy interpreter for a dynamically typed language with two types:
// int and pairs

#ifndef INTERP_H
#define INTERP_H

#define STACK_MAX 256
#define INITIAL_GC_THRESHOLD 8

// Define the two possibles types
typedef enum { OBJ_INT, OBJ_PAIR } ObjectType;

// Define an object that can either be a int or a pair
typedef struct sObject {
  ObjectType type;
  unsigned char marked;
  struct sObject *next;

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
  int stackSize;
  Object *firstObject;

  // We need to keep track of the number of created object to now when to run
  // the GC
  int numObjects;
  int maxObjects;
} VM;

// Function that initialize a VM
VM *initVM();
void freeVM(VM *vm);
void gc(VM *vm);

void assert(int condition, const char *message);

// Create a new Object
Object *newObject(VM *vm, ObjectType type);

// Stack Manipulation
void pushStack(VM *vm, Object *obj);
Object *popStack(VM *vm);

void pushInt(VM *vm, int value);
Object *pushPair(VM *vm);

// Handle GC
void mark(Object *object);
void markAll(VM *vm);
void sweep(VM *vm);

#endif
