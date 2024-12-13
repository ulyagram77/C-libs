#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap_sort.h"

// Допоміжна функція для обміну двох елементів масиву
static void swap_elements(DynArr *arr, size_t i, size_t j, SortStats *stats)
{
  if (i == j)
    return;
  // Виділяємо тимчасовий буфер під один елемент
  void *temp = malloc(arr->elem_size);
  if (!temp)
  {
    perror("Failed to allocate memory for swap");
    exit(EXIT_FAILURE);
  }

  void *elem_i = (char *)arr->data + i * arr->elem_size;
  void *elem_j = (char *)arr->data + j * arr->elem_size;

  memcpy(temp, elem_i, arr->elem_size);
  memcpy(elem_i, elem_j, arr->elem_size);
  memcpy(elem_j, temp, arr->elem_size);

  free(temp);

  stats->swaps++;
}

// Допоміжна функція для порівняння елементів та підрахунку порівнянь
static int compare_elements(const void *a, const void *b, int (*compare)(const void *, const void *), SortStats *stats)
{
  stats->comparisons++;
  return compare(a, b);
}

// Підтримка властивостей купи (heapify)
// Для сортування за зростанням - будуємо max-heap (батько більший за нащадків).
// Для сортування за спаданням - будуємо min-heap (батько менший за нащадків).
static void heapify(DynArr *arr, size_t n, size_t i, SortOrder order, int (*compare)(const void *, const void *), SortStats *stats)
{
  size_t largest_or_smallest = i;
  size_t left = 2 * i + 1;
  size_t right = 2 * i + 2;

  // Залежно від порядку, вибираємо напрямок порівняння
  // Для ASCENDING: ми хочемо max-heap, тобто батько має бути більшим за дітей.
  // largest_or_smallest буде найбільшим
  // Для DESCENDING: ми хочемо min-heap, тобто батько має бути меншим за дітей.
  // largest_or_smallest буде найменшим.

  // Перевірка лівого нащадка
  if (left < n)
  {
    void *current = (char *)arr->data + largest_or_smallest * arr->elem_size;
    void *child = (char *)arr->data + left * arr->elem_size;
    int cmp = compare_elements(child, current, compare, stats);

    if ((order == ASCENDING && cmp > 0) || (order == DESCENDING && cmp < 0))
    {
      largest_or_smallest = left;
    }
  }

  // Перевірка правого нащадка
  if (right < n)
  {
    void *current = (char *)arr->data + largest_or_smallest * arr->elem_size;
    void *child = (char *)arr->data + right * arr->elem_size;
    int cmp = compare_elements(child, current, compare, stats);

    if ((order == ASCENDING && cmp > 0) || (order == DESCENDING && cmp < 0))
    {
      largest_or_smallest = right;
    }
  }

  // Якщо найбільший/найменший не батько, то міняємо місцями та продовжуємо
  if (largest_or_smallest != i)
  {
    swap_elements(arr, i, largest_or_smallest, stats);
    heapify(arr, n, largest_or_smallest, order, compare, stats);
  }
}

void heap_sort_dyn_arr(DynArr *arr, SortOrder order, int (*compare)(const void *, const void *))
{
  SortStats stats = {0, 0};

  size_t n = arr->size;
  if (n < 2)
  {
    // Масив уже відсортований або недостатньо даних для сортування
    if (order == ASCENDING)
    {
      printf("\n\033[32m\033[0m Sorting order: \033[32masc\033[0m\n");
    }
    else
    {
      printf("\n\033[32m\033[0m Sorting order: \033[32mdesc\033[0m\n");
    }

    printf("\033[32m󰓡\033[0m Number of swaps: \033[32m%zu\033[0m\n", stats.swaps);
    printf("\033[32m\033[0m Number of comparisons: \033[32m%zu\033[0m\n", stats.comparisons);
    return;
  }

  // Побудова купи
  for (int i = (int)(n / 2) - 1; i >= 0; i--)
  {
    heapify(arr, n, (size_t)i, order, compare, &stats);
  }

  // Послідовне "виймання" елементів з купи
  for (size_t i = n - 1; i > 0; i--)
  {
    swap_elements(arr, 0, i, &stats);
    heapify(arr, i, 0, order, compare, &stats);
  }

  if (order == ASCENDING)
  {
    printf("\n\033[32m\033[0m Sorting order: \033[32masc\033[0m\n");
  }
  else
  {
    printf("\n\033[32m\033[0m Sorting order: \033[32mdesc\033[0m\n");
  }

  printf("\033[32m󰓡\033[0m Number of swaps: \033[32m%zu\033[0m\n", stats.swaps);
  printf("\033[32m\033[0m Number of comparisons: \033[32m%zu\033[0m\n", stats.comparisons);
}
