#ifndef SORT_COMMON_H
#define SORT_COMMON_H

#include <stddef.h>

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

#endif
