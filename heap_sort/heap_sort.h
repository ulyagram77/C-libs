#ifndef HEAP_SORT_H
#define HEAP_SORT_H

#include "sort_common.h"
#include "dyn_arr.h"

// Функція сортування динамічного масиву за допомогою купи (heap sort).
// Параметри:
// - arr: вказівник на динамічний масив
// - order: порядок сортування (ASCENDING або DESCENDING)
// - compare: функція порівняння елементів, подібна до qsort (повертає <0, якщо a<b; 0 якщо a==b; >0 якщо a>b)
void heap_sort_dyn_arr(DynArr *arr, SortOrder order, int (*compare)(const void *, const void *));

#endif
