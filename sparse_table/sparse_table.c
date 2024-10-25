#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int *values;
  int *colIndex;
  int *rowPtr;
  int nonZeroCount;
} CSRMatrix;

CSRMatrix create(int **matrix, int rows, int cols) {
  CSRMatrix csr;
  int nonzero_elem_count = 0;

  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      if (!(i % 2 == 0 && j % 2 == 0) && matrix[i][j] != 0) {
        nonzero_elem_count++;
      }
    }
  }

  csr.values = (int *)malloc(nonzero_elem_count * sizeof(int));
  csr.colIndex = (int *)malloc(nonzero_elem_count * sizeof(int));
  csr.rowPtr = (int *)malloc((rows + 1) * sizeof(int));
  csr.nonZeroCount = nonzero_elem_count;

  int k = 0;
  csr.rowPtr[0] = 0; // start of first row
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      if (!(i % 2 == 0 && j % 2 == 0) && matrix[i][j] != 0) {
        csr.values[k] = matrix[i][j];
        csr.colIndex[k] = j;
        k++;
      }
    }
    csr.rowPtr[i + 1] = k; // end of current row
  }

  return csr;
}

int get_element(CSRMatrix *csr, int row, int col) {
  for (size_t i = csr->rowPtr[row]; i < csr->rowPtr[row + 1]; i++) {
    if (csr->colIndex[i] == col) {
      return csr->values[i];
    }
  }

  return (row % 2 == 0 && col % 2 == 0) ? 0 : 0;
}

void print(CSRMatrix csr, int rows, int cols) {
  printf("\033[33mValues:\033[0m ");
  for (int i = 0; i < csr.nonZeroCount; i++) {
    printf("%d ", csr.values[i]);
  }
  printf("\n\033[33mColumn indexes for non-zero elements:\033[0m ");
  for (int i = 0; i < csr.nonZeroCount; i++) {
    printf("%d ", csr.colIndex[i]);
  }
  printf("\n\033[33mPointers to the beginning of each row in the values "
         "array:\033[0m ");
  for (int i = 0; i <= rows; i++) {
    printf("%d ", csr.rowPtr[i]);
  }
  printf("\n");
}

void destroy(CSRMatrix *csr) {

  if (csr->values != NULL) {
    free(csr->values);
    csr->values = NULL;
  }
  if (csr->colIndex != NULL) {
    free(csr->colIndex);
    csr->colIndex = NULL;
  }
  if (csr->rowPtr != NULL) {
    free(csr->rowPtr);
    csr->rowPtr = NULL;
  }
  csr->nonZeroCount = 0;
}
