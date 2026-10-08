#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct node
{
    int number;
    struct node *next;
} node;

// Prototypes
void append(node **list, int value);
void prepend(node **list, int value);
void delete(node **list, int value);
int count(node *list);
void show(node *list);
void free_list(node *list);

#endif // LINKED_LIST_H
