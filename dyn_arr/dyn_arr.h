#ifndef DYN_ARR_H
#define DYN_ARR_H

#include <stdio.h>
#include <stdlib.h>

typedef struct DynArr
{
  void *data;
  size_t elem_size;
  size_t size;
  size_t capacity;
} DynArr;

DynArr *init_dyn_arr(size_t element_size, size_t initial_capacity);
void push_dyn_arr(DynArr *array, void *element);
void *get_elem_dyn_arr(DynArr *array, size_t index);
void destroy_dyn_arr(DynArr *array);

#endif