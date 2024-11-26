#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 8

typedef struct Block {
  char data[BLOCK_SIZE];
  int filled;
  struct Block *next;
} Block;

typedef struct {
  Block *head;
  Block *tail;
  size_t length;
  size_t size;
} BlockString;

BlockString *init_block_string() {
  BlockString *str = (BlockString *)malloc(sizeof(BlockString));
  if (str) {
    str->head = str->tail = NULL;
    str->length = 0;
    str->size = sizeof(BlockString);
  }
  return str;
}

void append_to_block_string(BlockString *str, const char *text) {
  size_t textLength = strlen(text);
  size_t i = 0;

  while (i < textLength) {
    if (!str->tail || str->tail->filled == BLOCK_SIZE) {

      Block *newBlock = (Block *)malloc(sizeof(Block));
      if (!newBlock)
        return;
      memset(newBlock->data, '\0', BLOCK_SIZE);
      newBlock->filled = 0;
      newBlock->next = NULL;

      if (str->tail) {
        str->tail->next = newBlock;
      } else {
        str->head = newBlock;
      }
      str->tail = newBlock;

      str->size += sizeof(Block);
    }

    while (i < textLength && str->tail->filled < BLOCK_SIZE) {
      str->tail->data[str->tail->filled++] = text[i++];
      str->length++;
    }
  }
}

char *get_block_string(BlockString *str) {
  char *result = malloc((str->length + 1) * sizeof(char));
  Block *current = str->head;
  size_t i = 0;

  while (current) {
    strncpy(result + i, current->data, current->filled);
    i += current->filled;
    current = current->next;
  }
  result[str->length] = '\0';
  return result;
}

void print_block_string(BlockString *str) {
  Block *current = str->head;
  printf("String: ");
  while (current) {
    for (int i = 0; i < current->filled; i++) {
      putchar(current->data[i]);
    }
    current = current->next;
  }
  printf("\n");
  printf("Length: %zu\n", str->length);
  printf("Total size: %zu bytes\n", str->size);
}

void destroy_block_string(BlockString *str) {
  Block *current = str->head;
  while (current) {
    Block *next = current->next;
    free(current);
    current = next;
  }
  free(str);
}
