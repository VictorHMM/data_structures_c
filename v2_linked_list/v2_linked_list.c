#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include "v2_linked_list.h"

void free_node(node *nd);

node *append(node **list, node *nd)
{
  node *new_node = nd;
  new_node->next = NULL;

  if (*list == NULL)
  {
    *list = new_node;
    return *list;
  }
  else
  {
    for (node *n = *list; n != NULL; n = n->next)
    {
      if (n->next == NULL)
      {
        n->next = new_node;
        return *list;
      }
    }
  }
  return *list;
}

node *prepend(node **list, node nd)
{
  return *list;
}

bool delete(node **list, char *name)
{
  // List empty
  if (*list == NULL)
  {
    system("clear");
    printf("List empty\n");
    return false;
  }

  // Contact not found
  if (!(find(*list, name)))
  {
    system("clear");
    printf("Contact %s not found.\n", name);
    return false;
  }
  
  node *nd = *list;
  // List not empty and contact present in list.
  // Single node
  if (nd->next == NULL)
  {
    free_node(nd);
    *list = NULL;
    nd = NULL;
    return true;
  }
  else if (strcmp(nd->name, name) == 0) // Multiple nodes. Deletes first one
  {
    *list = (*list)->next;
    free_node(nd);
    nd = NULL;
    return true;
  }
  else // Multiple nodes. Deletes somewhere in the middle.
  {
    while (nd->next != NULL)
    {
      if (strcmp(nd->next->name, name) == 0)
      {
        node *tmp = nd->next;
        nd->next = nd->next->next;
        free_node(tmp);
        tmp = NULL;
        return true;
      }
      else
      {
        nd = nd->next;
      }
    }
    // Deletes last node
    free_node(nd);
    nd = NULL;
    return true;
  }
  return false;
}

void show(node *list)
{
  if (list == NULL)
  {
    printf("List empty\n");
    return;
  }
  else
  {
    node *nd = list;
    while (nd != NULL)
    {
      printf("Name: %s\n", nd->name);
      printf("Number: %s\n", nd->number);
      printf("Address: %p\n", nd);
      nd = nd->next;
    }
  }
}

node* find(node *list, char *name)
{
  if (list == NULL)
  {
    return list;
  }

  node *nd = list;
  while(nd != NULL)
  {
    if (strcmp(nd->name, name) == 0)
      return nd;
    nd = nd->next; 
  }
  return NULL;
}

void free_list(node *list)
{
  if (list == NULL)
  {
    return;
  }
  else
  {
    node *nd = list;
    list = list->next;
    free_node(nd);
    free_list(list);
  }
}

int count(node *list)
{
  int counter = 0;
  node *nd = list;

  while (nd != NULL)
  {
    nd = nd->next;
    counter++;
  }
  return counter;
}

void free_node(node *nd)
{
  free(nd->name);
  free(nd->number);
  free(nd);
}
