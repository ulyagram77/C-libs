#include <stdio.h>
#include <stdlib.h>

typedef struct
{
  int data;
  int priority;
} PriorityQueueElement;

// Array based priority queue
typedef struct
{
  PriorityQueueElement *elements;
  int size;
  int capacity;
  int front;
  int rear;
  size_t allocated_memory;
} PriorityQueue;

PriorityQueue init_priority_queue(int capacity)
{
  PriorityQueue pq;
  pq.elements =
      (PriorityQueueElement *)malloc(sizeof(PriorityQueueElement) * capacity);
  pq.size = 0;
  pq.capacity = capacity;
  pq.front = 0;
  pq.rear = 0;
  pq.allocated_memory = sizeof(PriorityQueueElement) * capacity;
  return pq;
}

void resize(PriorityQueue *pq)
{
  pq->capacity *= 2;
  pq->elements = (PriorityQueueElement *)realloc(
      pq->elements, sizeof(PriorityQueueElement) * pq->capacity);
  pq->allocated_memory = sizeof(PriorityQueueElement) * pq->capacity;
}

void push_priority_queue(PriorityQueue *pq, int data, int priority)
{
  if (pq->size == pq->capacity)
  {
    resize(pq);
  }

  PriorityQueueElement newElem = {data, priority};

  int i = pq->size - 1;

  while (i >= 0 && pq->elements[i].priority < priority)
  {
    pq->elements[i + 1] = pq->elements[i];
    i--;
  }

  pq->elements[i + 1] = newElem;
  pq->size++;
}

PriorityQueueElement pop_priority_queue(PriorityQueue *pq)
{
  if (pq->size == 0)
  {
    printf("Priority queue is empty.\n");
    PriorityQueueElement emptyElement = {0, 0};
    return emptyElement;
  }

  PriorityQueueElement topElement = pq->elements[pq->front];

  for (int i = 0; i < pq->size - 1; i++)
  {
    pq->elements[i] = pq->elements[i + 1];
  }

  pq->size--;
  return topElement;
}

void destroy_priority_queue(PriorityQueue *pq)
{
  free(pq->elements);
  pq->allocated_memory = 0;
}

void print_priority_queue(PriorityQueue *pq)
{
  if (pq->size == 0)
  {
    printf("Priority queue is empty.\n");
    return;
  }

  for (int i = 0; i < pq->size; i++)
  {
    printf("Value: %d, Priority: %d", pq->elements[i].data, pq->elements[i].priority);
    if (i < pq->size - 1)
    {
      printf("\n");
    }
  }
  printf("\n");
}
