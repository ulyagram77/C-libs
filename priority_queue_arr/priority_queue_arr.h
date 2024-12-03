#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

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

PriorityQueue init_priority_queue(int capacity);
void push_priority_queue(PriorityQueue *pq, int data, int priority);
PriorityQueueElement pop_priority_queue(PriorityQueue *pq);
void print_priority_queue(PriorityQueue *pq);
void destroy_priority_queue(PriorityQueue *pq);

#endif 