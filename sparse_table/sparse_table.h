#ifndef SPARSE_TABLE_H
#define SPARSE_TABLE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int *values;
  int *colIndex;
  int *rowPtr;
  int nonZeroCount;
} CSRMatrix;

CSRMatrix create(int **matrix, int rows, int cols);

int get_element(CSRMatrix *csr, int row, int col);

void print(CSRMatrix csr, int rows, int cols);

void destroy(CSRMatrix *csr);

#endif