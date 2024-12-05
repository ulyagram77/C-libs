#ifndef TREE_SORT_H
#define TREE_SORT_H

#include <stddef.h>
#include "dyn_arr.h"

typedef struct TreeNode
{
  void *data;
  struct TreeNode *left;
  struct TreeNode *right;
} TreeNode;

void sort_with_tree(DynArr *arr);

#endif