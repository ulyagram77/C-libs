#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 8

typedef struct Block {
  char data[BLOCK_SIZE];
  struct Block *next;
} Block;

typedef struct {
  Block *head;
  Block *tail;
  size_t length;
  size_t size;
} BlockString;

BlockString *init_block_string();
char *get_block_string(BlockString *str);
void append_to_block_string(BlockString *str, const char *text);
void print_block_string(BlockString *str);
void destroy_block_string(BlockString *str);