#ifndef HASH_TABLE_CHAINED_H
#define HASH_TABLE_CHAINED_H

#define TABLE_SIZE 10
#define MAX_NAME_LENGTH 50
#define MAX_EMAIL_LENGTH 50

typedef struct Node
{
  int id;
  char name[MAX_NAME_LENGTH];
  char email[MAX_EMAIL_LENGTH];
  struct Node *next;
} Node;

int ht_function(int key);
void ht_insert(int id, const char *name, const char *email);
Node *ht_search(int id);
void ht_print();

#endif 