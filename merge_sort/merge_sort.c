#include "merge_sort.h"

int compare_elements(void *a, void *b, size_t elem_size, SortOrder order)
{
  if (order == ASCENDING)
  {
    return memcmp(a, b, elem_size);
  }
  else
  {
    return memcmp(b, a, elem_size);
  }
}

void merge(DynArr *arr, size_t left, size_t mid, size_t right, SortOrder order, SortStats *stats)
{
  size_t left_size = mid - left + 1;
  size_t right_size = right - mid;

  void *left_arr = malloc(left_size * arr->elem_size);
  void *right_arr = malloc(right_size * arr->elem_size);

  if (!left_arr || !right_arr)
  {
    perror("Failed to allocate memory for merge");
    exit(EXIT_FAILURE);
  }

  memcpy(left_arr, (char *)arr->data + left * arr->elem_size, left_size * arr->elem_size);
  memcpy(right_arr, (char *)arr->data + (mid + 1) * arr->elem_size, right_size * arr->elem_size);

  size_t i = 0, j = 0, k = left;

  while (i < left_size && j < right_size)
  {
    stats->comparisons++;
    if (compare_elements((char *)left_arr + i * arr->elem_size, (char *)right_arr + j * arr->elem_size, arr->elem_size, order) <= 0)
    {
      memcpy((char *)arr->data + k * arr->elem_size, (char *)left_arr + i * arr->elem_size, arr->elem_size);
      i++;
    }
    else
    {
      memcpy((char *)arr->data + k * arr->elem_size, (char *)right_arr + j * arr->elem_size, arr->elem_size);
      j++;
    }
    k++;
    stats->swaps++;
  }

  while (i < left_size)
  {
    memcpy((char *)arr->data + k * arr->elem_size, (char *)left_arr + i * arr->elem_size, arr->elem_size);
    i++;
    k++;
    stats->swaps++;
  }

  while (j < right_size)
  {
    memcpy((char *)arr->data + k * arr->elem_size, (char *)right_arr + j * arr->elem_size, arr->elem_size);
    j++;
    k++;
    stats->swaps++;
  }

  free(left_arr);
  free(right_arr);
}

void merge_sort(DynArr *arr, size_t left, size_t right, SortOrder order, SortStats *stats)
{
  if (left < right)
  {
    size_t mid = left + (right - left) / 2;

    merge_sort(arr, left, mid, order, stats);
    merge_sort(arr, mid + 1, right, order, stats);
    merge(arr, left, mid, right, order, stats);
  }
}

void merge_sort_dyn_arr(DynArr *arr, SortOrder order)
{
  SortStats stats = {0, 0};
  merge_sort(arr, 0, arr->size - 1, order, &stats);

  if (order == ASCENDING)
  {
    printf("\n\033[32m\033[0m Sorting order: \033[32masc\033[0m\n");
  }
  else
  {
    printf("\n\033[32m\033[0m Sorting order: \033[32mdesc\033[0m\n");
  }

  printf("\033[32m󰓡\033[0m Number of swaps: \033[32m%d\033[0m\n", stats.swaps);
  printf("\033[32m\033[0m Number of comparisons: \033[32m%d\033[0m\n", stats.comparisons);
}