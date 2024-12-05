#include "tree_sort.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int compare(void *a, void *b, size_t elem_size)
{
  return memcmp(a, b, elem_size);
}

TreeNode *insert_to_tree(TreeNode *root, void *data, size_t elem_size, int *comparison_count, int *move_count)
{
  if (root == NULL)
  {
    TreeNode *new_node = malloc(sizeof(TreeNode));
    new_node->data = malloc(elem_size);
    memcpy(new_node->data, data, elem_size);
    new_node->left = new_node->right = NULL;
    (*move_count)++;
    return new_node;
  }

  (*comparison_count)++;
  int cmp = compare(data, root->data, elem_size);
  if (cmp < 0)
  {
    root->left = insert_to_tree(root->left, data, elem_size, comparison_count, move_count);
  }
  else if (cmp > 0)
  {
    root->right = insert_to_tree(root->right, data, elem_size, comparison_count, move_count);
  }

  return root;
}

void inorder_tree(TreeNode *root, void *arr, size_t elem_size, size_t *index, int *move_count)
{
  if (root == NULL)
    return;
  inorder_tree(root->left, arr, elem_size, index, move_count);

  memcpy((char *)arr + (*index) * elem_size, root->data, elem_size);
  (*index)++;
  (*move_count)++;

  inorder_tree(root->right, arr, elem_size, index, move_count);
}

void destroy_tree(TreeNode *root)
{
  if (root == NULL)
    return;
  destroy_tree(root->left);
  destroy_tree(root->right);
  free(root->data);
  free(root);
}

void sort_with_tree(DynArr *arr)
{
  int comparison_count = 0, move_count = 0;
  TreeNode *root = NULL;

  for (size_t i = 0; i < arr->size; i++)
  {
    void *element = (char *)arr->data + i * arr->elem_size;
    root = insert_to_tree(root, element, arr->elem_size, &comparison_count, &move_count);
  }

  size_t index = 0;
  inorder_tree(root, arr->data, arr->elem_size, &index, &move_count);

  printf("\033[32m󰓡\033[0m Number of swaps: \033[32m%d\033[0m\n", move_count);
  printf("\033[32m\033[0m Number of comparisons: \033[32m%d\033[0m\n", comparison_count);

  destroy_tree(root);
}