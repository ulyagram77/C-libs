#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tree_sort.h"

static gint compare_elements(const void *a, const void *b, gpointer user_data)
{
  size_t elem_size = *(size_t *)user_data;
  return memcmp(a, b, elem_size);
}

static void add_to_array(gpointer key, gpointer value, gpointer user_data)
{
  DynArr *arr = (DynArr *)user_data;
  void *new_element = malloc(arr->elem_size);
  if (new_element == NULL)
  {
    perror("Failed to allocate memory for new element");
    return;
  }
  memcpy(new_element, key, arr->elem_size);
  push_dyn_arr(arr, new_element); // Копируем данные в новый элемент и добавляем в массив
}

void sort_with_gtree(DynArr *arr)
{
  if (arr->size == 0)
  {
    printf("Array is empty, nothing to sort\n");
    return;
  }

  printf("Starting tree sort, array size: %zu\n", arr->size);

  // Создаем дерево с пользовательской функцией сравнения
  GTree *tree = g_tree_new_full(compare_elements, &arr->elem_size, NULL, NULL);

  // Вставляем элементы массива в дерево
  for (size_t i = 0; i < arr->size; i++)
  {
    void *element = (char *)arr->data + i * arr->elem_size;
    printf("Inserting element at index %zu: %p\n", i, element);

    // Проверка на валидность указателя
    if (element == NULL)
    {
      printf("Error: Invalid element pointer at index %zu\n", i);
      continue;
    }

    g_tree_insert(tree, element, NULL);
  }

  // Очищаем массив перед заполнением его отсортированными элементами
  arr->size = 0;

  // Проходим по дереву и заполняем массив отсортированными элементами
  g_tree_foreach(tree, add_to_array, arr);

  // Освобождаем дерево
  g_tree_destroy(tree);
}
