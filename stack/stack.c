#include <stdio.h>
#include <stdlib.h>

typedef struct stack_elem {
  int data;
  struct stack_elem *next;
} STACK;

STACK *push(STACK *top, int data) {
  STACK *ptr = malloc(sizeof(STACK));
  ptr->data = data;
  ptr->next = top;
  return ptr;
}

STACK *pop(STACK *top) {
  if (top == NULL)
    return top;

  printf("Deleted: %d\n", top->data);
  STACK *ptr_next = top->next;
  free(top);
  return ptr_next;
}

void show(const STACK *top) {
  const STACK *current = top;
  while (current != NULL) {
    printf("%d\n", current->data);
    current = current->next;
  }
}