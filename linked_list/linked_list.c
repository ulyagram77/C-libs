#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

Node *create_node_linked_list(void *data)
{
  Node *newNode = (Node *)malloc(sizeof(Node));
  if (!newNode)
  {
    perror("Cannot able to allocate memory!\n");
    exit(EXIT_FAILURE);
  }
  newNode->data = data;
  newNode->next = NULL;
  return newNode;
}

void insert_head_linked_list(Node **head, void *data)
{
  Node *newNode = create_node_linked_list(data);
  newNode->next = *head;
  *head = newNode;
}

void insert_after_element_linked_list(Node *node, void *data)
{
  if (!node)
    return;
  Node *newNode = create_node_linked_list(data);
  newNode->next = node->next;
  node->next = newNode;
}

void delete_node_linked_list(Node **head, void *target, CompareFunc comparer, void (*free_data)(void *))
{
  if (!head || !*head)
    return;

  Node *temp = *head;
  Node *prev = NULL;

  while (temp && comparer(temp->data, target) != 0)
  {
    prev = temp;
    temp = temp->next;
  }

  if (!temp)
    return;

  if (prev)
  {
    prev->next = temp->next;
  }
  else
  {
    *head = temp->next;
  }

  if (free_data)
  {
    free_data(temp->data);
  }
  free(temp);
}

Node *find_element_linked_list(Node *head, void *target, CompareFunc comparer)
{
  while (head)
  {
    if (comparer(head->data, target) == 0)
    {
      return head;
    }
    head = head->next;
  }
  return NULL;
}

void destroy_linked_list(Node **head, void (*free_data)(void *))
{
  while (*head)
  {
    Node *temp = *head;
    *head = (*head)->next;

    if (free_data)
    {
      free_data(temp->data);
    }
    free(temp);
  }
}

void print_linked_list(Node *head, void (*print_data)(const void *))
{
  while (head)
  {
    print_data(head->data);
    head = head->next;
  }
}
