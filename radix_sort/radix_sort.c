#include "radix_sort.h"

int get_digit(int number, int place)
{
  return (number / place) % 10;
}

int get_max(DynArr *arr)
{
  int max = *(int *)get_elem_dyn_arr(arr, 0);
  for (size_t i = 1; i < arr->size; i++)
  {
    int value = *(int *)get_elem_dyn_arr(arr, i);
    if (value > max)
    {
      max = value;
    }
  }
  return max;
}

void counting_sort(DynArr *arr, int place, SortOrder order, SortStats *stats)
{
  size_t count[10] = {0};
  int *output = malloc(arr->size * sizeof(int));

  if (!output)
  {
    perror("Failed to allocate memory for output array");
    exit(EXIT_FAILURE);
  }

  for (size_t i = 0; i < arr->size; i++)
  {
    int digit = get_digit(*(int *)get_elem_dyn_arr(arr, i), place);
    count[digit]++;
  }

  if (order == ASCENDING)
  {
    for (int i = 1; i < 10; i++)
    {
      count[i] += count[i - 1];
    }
  }
  else
  {
    for (int i = 8; i >= 0; i--)
    {
      count[i] += count[i + 1];
    }
  }

  for (int i = arr->size - 1; i >= 0; i--)
  {
    int digit = get_digit(*(int *)get_elem_dyn_arr(arr, i), place);
    output[--count[digit]] = *(int *)get_elem_dyn_arr(arr, i);
    stats->swaps++;
  }

  for (size_t i = 0; i < arr->size; i++)
  {
    memcpy((char *)arr->data + i * arr->elem_size, &output[i], sizeof(int));
  }

  free(output);
}

void radix_sort(DynArr *arr, SortOrder order, SortStats *stats)
{
  int max = get_max(arr);

  for (int place = 1; max / place > 0; place *= 10)
  {
    counting_sort(arr, place, order, stats);
    stats->comparisons += arr->size;
  }
}

void radix_sort_dyn_arr(DynArr *arr, SortOrder order)
{
  SortStats stats = {0, 0};
  radix_sort(arr, order, &stats);

  if (order == ASCENDING)
  {
    printf("\n\033[32m\033[0m Sorting order: \033[32mAscending\033[0m\n");
  }
  else
  {
    printf("\n\033[32m\033[0m Sorting order: \033[32mDescending\033[0m\n");
  }

  printf("Sorting completed.\n");
  printf("Comparisons: %zu\n", stats.comparisons);
  printf("Swaps: %zu\n", stats.swaps);
}