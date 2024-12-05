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
  push_dyn_arr(arr, key);
}

void sort_with_gtree(DynArr *arr)
{
  if (arr->size == 0)
    return;

  // Создаем дерево с пользовательской функцией сравнения
  GTree *tree = g_tree_new(compare_elements);

  // Вставляем элементы массива в дерево
  for (size_t i = 0; i < arr->size; i++)
  {
    void *element = malloc(arr->elem_size);
    if (!element)
    {
      perror("Failed to allocate memory for element");
      g_tree_destroy(tree);
      return;
    }

    memcpy(element, (char *)arr->data + i * arr->elem_size, arr->elem_size);
    g_tree_insert(tree, element, NULL);
  }

  // Очищаем массив перед заполнением его отсортированными элементами
  arr->size = 0;

  // Проходим по дереву и заполняем массив
  g_tree_foreach(tree, add_to_array, arr);

  // Освобождаем дерево и временные элементы
  g_tree_destroy(tree);
}
