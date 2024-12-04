#include "dyn_arr.h"

// init arr
DynArr *init_dyn_arr(size_t element_size, size_t initial_capacity)
{
  DynArr *arr = malloc(sizeof(DynArr));
  if (!arr)
  {
    perror("Failed to allocate memory for array");
    exit(EXIT_FAILURE);
  }

  arr->data = calloc(element_size, initial_capacity);
  if (!arr->data)
  {
    perror("Failed to allocate memory for array data");
    free(arr);
    exit(EXIT_FAILURE);
  }

  arr->elem_size = element_size;
  arr->size = 0;
  arr->capacity = initial_capacity;

  return arr;
}

// resize arr
void _resize_arr(DynArr *arr, size_t new_capacity)
{
  arr->data = realloc(arr->data, arr->elem_size * new_capacity);
  if (!arr->data)
  {
    perror("Failed to reallocate memory");
    exit(EXIT_FAILURE);
  }
  arr->capacity = new_capacity;
}

// push elem to arr
void push_dyn_arr(DynArr *arr, void *element)
{
  if (arr->size == arr->capacity)
  {
    _resize_arr(arr, arr->capacity * 2);
  }

  memcpy((char *)arr->data + arr->size * arr->elem_size, element, arr->elem_size);
  arr->size++;
}

// get elem by index from arr
void *get_elem_dyn_arr(DynArr *arr, size_t index)
{
  if (index >= arr->size)
  {
    fprintf(stderr, "Index out of bounds\n");
    return NULL;
  }
  return (char *)arr->data + index * arr->elem_size;
}

// destroy arr
void destroy_dyn_arr(DynArr *arr)
{
  for (size_t i = 0; i < arr->size; i++)
  {
    void *elem = get_elem_dyn_arr(arr, i);
    free(elem);
  }
  free(arr->data);
  free(arr);
}
