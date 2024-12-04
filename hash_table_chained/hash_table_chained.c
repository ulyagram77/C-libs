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

// Линейный поиск
void ht_linear_search(int id)
{
  clock_t start_time = clock(); // Начало времени
  int comparisons = 0;          // Счетчик сравнений

  for (int i = 0; i < TABLE_SIZE; i++)
  {
    Node *current = hashTable[i];
    while (current != NULL)
    {
      comparisons++;
      if (current->id == id)
      {
        clock_t end_time = clock(); // Конец времени
        double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        printf("\n[ЛИНЕЙНЫЙ ПОИСК] Найдено: ID: %d, Name: %s, Email: %s\n", current->id, current->name, current->email);
        printf("Количество сравнений: %d\n", comparisons);
        printf("Время выполнения: %.6f секунд\n", elapsed_time);
        return;
      }
      current = current->next;
    }
  }

  // Если не найдено
  clock_t end_time = clock();
  double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
  printf("\n[ЛИНЕЙНЫЙ ПОИСК] Элемент с ID %d не найден.\n", id);
  printf("Количество сравнений: %d\n", comparisons);
  printf("Время выполнения: %.6f секунд\n", elapsed_time);
}

// Линейный поиск с барьером
void ht_linear_search_with_barrier(int id)
{
  clock_t start_time = clock(); // Начало времени
  int comparisons = 0;          // Счетчик сравнений

  // Устанавливаем барьер: добавляем временный элемент в конец каждого списка
  for (int i = 0; i < TABLE_SIZE; i++)
  {
    Node *barrier = (Node *)malloc(sizeof(Node));
    barrier->id = id; // ID барьера совпадает с искомым
    barrier->next = NULL;

    Node *current = hashTable[i];
    if (current == NULL)
    {
      hashTable[i] = barrier; // Если список пуст, просто добавляем барьер
    }
    else
    {
      while (current->next != NULL)
      {
        current = current->next;
      }
      current->next = barrier; // Добавляем барьер в конец списка
    }
  }

  // Поиск с барьером
  for (int i = 0; i < TABLE_SIZE; i++)
  {
    Node *current = hashTable[i];
    while (current != NULL)
    {
      comparisons++;
      if (current->id == id)
      {
        clock_t end_time = clock(); // Конец времени
        double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

        // Удаляем барьеры
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

        printf("\n[ПОИСК С БАРЬЕРОМ] Найдено: ID: %d, Name: %s, Email: %s\n", current->id, current->name, current->email);
        printf("Количество сравнений: %d\n", comparisons);
        printf("Время выполнения: %.6f секунд\n", elapsed_time);
        return;
      }
      current = current->next;
    }
  }

  // Если не найдено
  clock_t end_time = clock();
  double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
  printf("\n[ПОИСК С БАРЬЕРОМ] Элемент с ID %d не найден.\n", id);
  printf("Количество сравнений: %d\n", comparisons);
  printf("Время выполнения: %.6f секунд\n", elapsed_time);
}
