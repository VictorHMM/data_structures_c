#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../io/io.h"
#include "linked_list.h"

int main(void)
{
    node *list = NULL;
    while(true)
    {
        printf("#####\n");
        char command = get_char("(A)ppend\n(C)ount\n(D)elete\n(P)repend\n(S)how\n(E)xit\n(F)ree\nCommand: ");
        system("clear");
        if (command == 'E')
        {
            free_list(list);
            list = NULL;
            break;
        }
        
        switch (command)
        {
            case 'A':
                append(&list, get_int("Value: "));
                break;
            case 'C':
                printf("# of nodes: %i\n", count(list));
                break;
            case 'D':
                delete(&list, get_int("Value: "));
                break;
            case 'P':
                prepend(&list, get_int("Value: "));
                break;
            case 'S':
                show(list);
                break;
            case 'F':
                free_list(list);
                list = NULL;
                break;
        }
    }
}

void append(node **list, int value)
{
    node *new_node = malloc(sizeof(node));
    if (new_node == NULL)
    {
        printf("Something went wrong.\n");
        return;
    }

    new_node->number = value;
    new_node->next = NULL;

    if (*list == NULL)
    {
        *list = new_node;
        return;
    }
    else
    {
        for (node *n = *list; n != NULL; n = n->next)
        {
            if (n->next == NULL)
            {
                n->next = new_node;
                return;
            }
        }
    }
}

void prepend(node **list, int value)
{
    node *new_node = malloc(sizeof(node));
    if (new_node == NULL)
    {
        printf("Something went wrong.\n");
        return;
    }
    new_node->number = value;
    new_node->next = *list;
    *list = new_node;
    return;
}

void delete(node **list, int value)
{
    if (*list == NULL)
    {
        system("clear");
        printf("List empty\n");
        return;
    }
    node *nd = *list;
    if (nd->number == value)
    {
        *list = nd->next;
        free(nd);
    }
    else
    {
        while (nd != NULL)
        {
            if (nd->next == NULL)
            {
                system("clear");
                system("mkdir test");
                printf("Number %i not found.\n", value);
                return;
            }
            if (nd->next->number == value)
            {
                node *tmp = nd->next;
                nd->next = nd->next->next;
                free(tmp);
                return;
            }
            nd = nd->next;
        }
    }
    return;
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
        node *n = list;
        while(n != NULL)
        {
            printf("%i\n", n->number);
            n = n->next;
        }
    }
}

void free_list(node *list)
{
    if (list == NULL)
    {
        return;
    }
    else
    {
        node *n = list;
        list = list->next;
        free(n);
        free_list(list);
    }
}

int count(node *list)
{
    int counter = 0;
    node *n = list;

    while(n != NULL)
    {
        n = n->next;
        counter++;
    }
    return counter;
}
