#include <stdio.h>
#include <stdlib.h>

typedef struct stack_elem {
  int data;
  struct stack_elem *next;
} STACK;

STACK *push(STACK *top, int data);
STACK *pop(STACK *top);
void show(const STACK *top);