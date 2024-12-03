#ifndef PRIORITY_QUEUE_LIST_H
#define PRIORITY_QUEUE_LIST_H

#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"

typedef struct LPQElement
{
  int value;
  int priority;
} LPQElement;

typedef struct LPQ
{
  Node *head;
  size_t allocated_memory;
} LPQ;

static int compare_priority(const void *a, const void *b);
// destroy lpq element
static void free_lpq_element(void *data);
// print lpq element
static void print_lpq_element(const void *data);
// create lpq
LPQ *init_lpq();
// add element to lpq
void enqueue_lpq(LPQ *queue, int value, int priority);
// delete hight priority element
int dequeue_lpq(LPQ *queue);
// destroy lpq
void destroy_lpq(LPQ *queue);
// print lpq
void print_lpq(LPQ *queue);

#endif