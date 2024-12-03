
#ifndef BUILDING_LIST_H
#define BUILDING_LIST_H

#include "linked_list.h"

typedef struct
{
  char name[100]; // Firm name
  Node *sublist;  // Sublist of occupied objects
} BuildingFirm;

BuildingFirm *create_building_firm(const char *name);
void destroy_building_firm(void *data);
void print_building_firm(const void *data);

#endif
