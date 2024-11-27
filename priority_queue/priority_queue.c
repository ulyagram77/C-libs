#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int data;
  int priority;
} PriorityQueueElement;

typedef struct {
  PriorityQueueElement *elements;
  int size;
  int capacity;
  int front;
  int rear;
} PriorityQueue;

PriorityQueue init_priority_queue(int capacity) {
  PriorityQueue pq;
  pq.elements =
      (PriorityQueueElement *)malloc(sizeof(PriorityQueueElement) * capacity);
  pq.size = 0;
  pq.capacity = capacity;
  return pq;
}

void resize(PriorityQueue *pq) {
  pq->capacity *= 2;
  pq->elements = (PriorityQueueElement *)realloc(
      pq->elements, sizeof(PriorityQueueElement) * pq->capacity);
}

void push_priority_queue(PriorityQueue *pq, int data, int priority) {
  if (pq->size == pq->capacity) {
    resize(pq);
  }

  PriorityQueueElement newElem = {data, priority};

  int i = pq->size - 1;

  while (i >= 0 && pq->elements[i].priority < priority) {
    pq->elements[i + 1] = pq->elements[i];
    i--;
  }

  pq->elements[i + 1] = newElem;
  pq->size++;
}

void pop_priority_queue(PriorityQueue *pq) {
  if (pq->size == 0) {
    printf("Priority queue is empty.\n");
    return;
  }

  return pq->elements[--pq->size];
}

void destroy_priority_queue(PriorityQueue *pq) { free(pq->elements); }
