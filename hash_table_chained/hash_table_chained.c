#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
  int index = ht_func(id);
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->id = id;
  strcpy(newNode->name, name);
  strcpy(newNode->email, email);
  newNode->next = hashTable[index];
  hashTable[index] = newNode;
}

Node *ht_search(int id)
{
  int index = ht_func(id);
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

void ht_linear_search(int id)
{
  clock_t start_time = clock();
  int comparisons = 0;

  for (int i = 0; i < TABLE_SIZE; i++)
  {
    Node *current = hashTable[i];
    while (current != NULL)
    {
      comparisons++;
      if (current->id == id)
      {
        clock_t end_time = clock();
        double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        printf("\n\033[32m\033[0m [LINEAR SEARCH] Found: ID: %d, Name: %s, Email: %s \033[32m\033[0m\n", current->id, current->name, current->email);
        printf("\033[32m\033[0m Comparisons amount: %d\n", comparisons);
        printf("\033[32m\033[0m Estimated time: %.3f ms\n", elapsed_time);
        return;
      }
      current = current->next;
    }
  }

  clock_t end_time = clock();
  double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC * 1000;
  printf("\n\033[21m\033[0m [LINEAR SEARCH] Element with ID %d was not found. \033[34m\033[0m\n", id);
  printf("\033[21m\033[0m Comparisons amount: %d\n", comparisons);
  printf("\033[21m\033[0m Estimated time: %.3f ms\n", elapsed_time);
}

void ht_linear_search_with_barrier(int id)
{
  clock_t start_time = clock();
  int comparisons = 0;

  for (int i = 0; i < TABLE_SIZE; i++)
  {
    Node *barrier = (Node *)malloc(sizeof(Node));
    barrier->id = id;
    barrier->next = NULL;

    Node *current = hashTable[i];
    if (current == NULL)
    {
      hashTable[i] = barrier;
    }
    else
    {
      while (current->next != NULL)
      {
        current = current->next;
      }
      current->next = barrier;
    }
  }

  for (int i = 0; i < TABLE_SIZE; i++)
  {
    Node *current = hashTable[i];
    while (current != NULL)
    {
      comparisons++;
      if (current->id == id)
      {
        clock_t end_time = clock();
        double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

        for (int j = 0; j < TABLE_SIZE; j++)
        {
          Node *prev = NULL;
          Node *cur = hashTable[j];
          while (cur != NULL)
          {
            if (cur->id == id && cur->next == NULL)
            {
              if (prev == NULL)
              {
                hashTable[j] = NULL;
              }
              else
              {
                prev->next = NULL;
              }
              free(cur);
              break;
            }
            prev = cur;
            cur = cur->next;
          }
        }

        printf("\n\033[32m\033[0m [BARRIER LINEAR SEARCH] Found: ID: %d, Name: %s, Email: %s \033[32m\033[0m\n", current->id, current->name, current->email);
        printf("\033[32m\033[0m Comparisons amount: %d\n", comparisons);
        printf("\033[32m\033[0m Estimated time: %.3f ms\n", elapsed_time);
        return;
      }
      current = current->next;
    }
  }

  clock_t end_time = clock();
  double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC * 1000;
  printf("\n\033[21m\033[0m [BARRIER LINEAR SEARCH] Element with ID %d was not found. \033[34m\033[0m\n", id);
  printf("\033[21m\033[0m Comparisons amount: %d\n", comparisons);
  printf("\033[21m\033[0m Estimated time: %.3f ms\n", elapsed_time);
}
