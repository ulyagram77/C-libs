#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_table_chained.h"

// hash table
Node *hashTable[TABLE_SIZE];

void ht_init()
{
  for (int i = 0; i < TABLE_SIZE; i++)
  {
    hashTable[i] = NULL;
  }
}

int ht_func(int key)
{
  int square = key * key;
  int mid = (square / 10) % 100;
  return mid % TABLE_SIZE;
}

void ht_insert(int id, const char *name, const char *email)
{
  int index = hashFunction(id);
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->id = id;
  strcpy(newNode->name, name);
  strcpy(newNode->email, email);
  newNode->next = hashTable[index];
  hashTable[index] = newNode;
}

Node *ht_search(int id)
{
  int index = hashFunction(id);
  Node *current = hashTable[index];
  while (current != NULL)
  {
    if (current->id == id)
    {
      return current;
    }
    current = current->next;
  }
  return NULL;
}

void ht_print()
{
  for (int i = 0; i < TABLE_SIZE; i++)
  {
    printf("Index %d: ", i);
    Node *current = hashTable[i];
    while (current != NULL)
    {
      printf("[ID: %d, Name: %s, Email: %s] -> ", current->id, current->name, current->email);
      current = current->next;
    }
    printf("NULL\n");
  }
}
