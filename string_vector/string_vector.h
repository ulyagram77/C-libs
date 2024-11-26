#ifndef STRING_VECTOR_H
#define STRING_VECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *data;
  size_t length;
  size_t capacity;
  size_t size;
} VectorString;

VectorString *init_vector_string(size_t capacity);
void append_to_vector_string(VectorString *str, const char *text);
void print_vector_string(VectorString *str);
void destroy_vector_string(VectorString *str);

#endif