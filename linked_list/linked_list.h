#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>

typedef struct Node
{
  void *data;
  struct Node *next;
} Node;

typedef int (*CompareFunc)(const void *a, const void *b);

// main operations
Node *create_node_linked_list(void *data);
void insert_head_linked_list(Node **head, void *data);
void insert_after_element_linked_list(Node *node, void *data);
void delete_node_linked_list(Node **head, void *target, CompareFunc comparer, void (*free_data)(void *));
Node *find_element_linked_list(Node *head, void *target, CompareFunc comparer);
void destroy_linked_list(Node **head, void (*free_data)(void *));

// util
void print_linked_list(Node *head, void (*print_data)(const void *));

#endif