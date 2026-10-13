#include <cs50.h>

#ifndef V2_LINKED_LIST_H
#define V2_LINKED_LIST_H

typedef struct node
{
  string name;  
  string number;
  struct node *next;
} node;

// Prototypes
node* append(node **list, node contact);
node* prepend(node **list, node contact);
node* delete(node **list, node *contact);
int count(node *list);
void show(node *list);
void free_list(node *list);

#endif // V2_LINKED_LIST_H
