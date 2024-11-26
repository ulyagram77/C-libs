#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *data;
  size_t length;
  size_t capacity;
  size_t size;
} VectorString;

VectorString *init_vector_string(size_t capacity) {
  VectorString *str = (VectorString *)malloc(sizeof(VectorString));
  if (!str) {
    printf("Error: Memory allocation failed.\n");
    return NULL;
  }

  str->data = (char *)malloc(capacity * sizeof(char));
  if (str->data) {
    str->length = 0;
    str->capacity = capacity;
    str->size = sizeof(VectorString) + capacity;
    str->data[0] = '\0';
  } else {
    free(str);
    return NULL;
  }

  return str;
}

void append_to_vector_string(VectorString *str, const char *text) {
  size_t newLength = str->length + strlen(text);
  if (newLength >= str->capacity) {
    size_t newCapacity = newLength * 2;
    char *newData = (char *)realloc(str->data, newCapacity * sizeof(char));
    if (!newData) {
      printf("Error: Memory reallocation failed.\n");
      return;
    }
    str->data = newData;
    str->capacity = newCapacity;
    str->size = sizeof(VectorString) + newCapacity;
  }

  strcat(str->data, text);
  str->length = newLength;
}

void print_vector_string(const VectorString *str) {
  printf("String: %s\n", str->data);
  printf("Length: %zu\n", str->length);
  printf("Capacity: %zu\n", str->capacity);
  printf("Total size: %zu bytes\n", str->size);
}

void destroy_vector_string(VectorString *str) {
  free(str->data);
  free(str);
}
