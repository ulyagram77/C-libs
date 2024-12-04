#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define TABLE_SIZE 300
#define MAX_NAME_LENGTH 50
#define MAX_EMAIL_LENGTH 50

typedef struct Node
{
  int id;
  char name[MAX_NAME_LENGTH];
  char email[MAX_EMAIL_LENGTH];
  struct Node *next;
} Node;

void ht_init();
int ht_func(int key);
void ht_insert(int id, const char *name, const char *email);
Node *ht_search(int id);
void ht_print();
void ht_linear_search(int id);
void ht_linear_search_with_barrier(int id);

#endif
