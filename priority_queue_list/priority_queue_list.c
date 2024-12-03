#include "priority_queue_list.h"
#include <stdlib.h>
#include <stdio.h>

static int compare_priority(const void *a, const void *b)
{
  const LPQElement *elemA = (const LPQ *)a;
  const LPQElement *elemB = (const LPQ *)b;

  if (elemA->priority != elemB->priority)
  {
    return elemB->priority - elemA->priority; // Max priority first
  }
  return 0; // FIFO when priority same
}

static void free_lpq_element(void *data)
{
  free(data);
}

static void print_lpq_element(const void *data)
{
  const LPQElement *elem = (const LPQ *)data;
  printf("Value: %d, Priority: %d\n", elem->value, elem->priority);
}

LPQ *init_lpq()
{
  LPQ *queue = (LPQ *)malloc(sizeof(LPQ));
  if (!queue)
  {
    perror("Cannot able to allocate memory!");
    exit(EXIT_FAILURE);
  }
  queue->head = NULL;
  return queue;
}

void enqueue_lpq(LPQ *queue, int value, int priority)
{
  LPQElement *newElement = (LPQElement *)malloc(sizeof(LPQElement));
  if (!newElement)
  {
    perror("Cannot able to allocate memory!");
    exit(EXIT_FAILURE);
  }
  newElement->value = value;
  newElement->priority = priority;

  Node **head = &(queue->head);

  if (!*head || compare_priority((*head)->data, newElement) > 0)
  {
    insert_head_linked_list(head, newElement);
  }
  else
  {
    Node *current = *head;
    while (current->next && compare_priority(current->next->data, newElement) <= 0)
    {
      current = current->next;
    }
    insert_after_element_linked_list(current, newElement);
  }
}

int dequeue_lpq(LPQ *queue)
{
  if (!queue->head)
  {
    printf("Queue is empty!\n");
    return -1;
  }
  LPQElement *top = (LPQElement *)queue->head->data;
  int value = top->value;
  delete_node_linked_list(&(queue->head), top, compare_priority, free_lpq_element);
  return value;
}

void destroy_lpq(LPQ *queue)
{
  destroy_linked_list(&(queue->head), free_lpq_element);
  free(queue);
}

void print_lpq(LPQ *queue)
{
  print_linked_list(queue->head, print_lpq_element);
}