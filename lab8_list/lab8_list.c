#include "lab8_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// init building list
BuildingFirm *create_building_firm(const char *name)
{
  BuildingFirm *firm = (BuildingFirm *)malloc(sizeof(BuildingFirm));
  if (!firm)
  {
    perror("Cannot allocate memory for BuildingFirm!");
    exit(EXIT_FAILURE);
  }
  strcpy(firm->name, name);
  firm->sublist = NULL;
  return firm;
}

// destroy building list
void destroy_building_firm(void *data)
{
  BuildingFirm *firm = (BuildingFirm *)data;
  if (firm->sublist)
  {
    destroy_linked_list(&firm->sublist, free);
  }
  free(firm);
}

// print building list
void print_building_firm(const void *data)
{
  const BuildingFirm *firm = (const BuildingFirm *)data;
  printf("\033[32m Building Firm:\033[0m %s\n", firm->name);

  if (firm->sublist)
  {
    printf("  Objects:\n");
    print_linked_list(firm->sublist, (void (*)(const void *))puts);
    puts("");
  }
  else
  {
    printf("  No objects.\n");
  }
}
