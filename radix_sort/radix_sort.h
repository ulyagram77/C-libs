#ifndef RADIX_SORT_H
#define RADIX_SORT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dyn_arr.h"

typedef enum
{
  ASCENDING,
  DESCENDING
} SortOrder;

typedef struct
{
  size_t comparisons;
  size_t swaps;
} SortStats;

void radix_sort_dyn_arr(DynArr *arr, SortOrder order);

#endif
