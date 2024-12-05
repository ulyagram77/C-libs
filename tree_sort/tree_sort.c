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
  push_dyn_arr(arr, key); // Добавляем элемент в динамический массив
}

void sort_with_gtree(DynArr *arr)
{
  if (arr->size == 0)
    return;

  // Создаем дерево с пользовательской функцией сравнения
  GTree *tree = g_tree_new(compare_elements);

  // Вставляем элементы массива в дерево, используя указатели без malloc
  for (size_t i = 0; i < arr->size; i++)
  {
    // Получаем указатель на элемент массива
    void *element = (char *)arr->data + i * arr->elem_size;
    g_tree_insert(tree, element, NULL); // Вставляем указатель в дерево
  }

  // Очищаем массив перед заполнением его отсортированными элементами
  arr->size = 0;

  // Проходим по дереву и заполняем массив отсортированными элементами
  g_tree_foreach(tree, add_to_array, arr);

  // Освобождаем дерево (не освобождаем элементы массива, так как мы их не malloc-им)
  g_tree_destroy(tree);
}
