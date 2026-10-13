#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include "v2_linked_list.h"

// int main(void)
// {
//     node *list = NULL;
//     while(true)
//     {
//         printf("#####\n");
//         char command = get_char("(A)ppend\n(C)ount\n(D)elete\n(P)repend\n(S)how\n(E)xit\n(F)ree\nCommand: ");
//         if (command == 'E')
//         {
//             free_list(list);
//             list = NULL;
//             break;
//         }

//         switch (command)
//         {
//             case 'A':
//                 append(&list, get_int("Value: "));
//                 break;
//             case 'C':
//                 printf("# of nodes: %i\n", count(list));
//                 break;
//             case 'D':
//                 delete(&list, get_int("Value: "));
//                 break;
//             case 'P':
//                 prepend(&list, get_int("Value: "));
//                 break;
//             case 'S':
//                 system("clear");
//                 show(list);
//                 break;
//             case 'F':
//                 free_list(list);
//                 list = NULL;
//                 break;
//         }
//     }
// }

node *append(node **list, node contact)
{
  node *new_contact = malloc(sizeof(node));
  // new_contact = &contact;
  new_contact->name = contact.name;
  new_contact->number = contact.number;
  // printf("%p\n%p\n", new_contact, new_contact->next);
  new_contact->next = NULL;
  // printf("%s\n", new_contact->name);
  if (*list == NULL)
  {
    *list = new_contact;
    //(*list)->next = NULL;
    return *list;
  }
  else
  {
    for (node *n = *list; n != NULL; n = n->next)
    {
      if (n->next == NULL)
      {
        n->next = new_contact;
        return *list;
      }
    }
  }
  return *list;
}

node *prepend(node **list, node contact)
{
  return *list;
}

node *delete(node **list, node *contact)
{
  if (*list == NULL)
  {
    system("clear");
    printf("List empty\n");
    return NULL;
  }
  node *nd = *list;
  if (nd->number == contact->number)
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
        printf("Number %s not found.\n", contact->number);
        return *list;
      }
      if (nd->next->number == contact->number)
      {
        node *tmp = nd->next;
        nd->next = nd->next->next;
        free(tmp);
        return *list;
      }
      nd = nd->next;
    }
  }
  return *list;
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
    while (n != NULL)
    {
      printf("Name: %s\n", n->name);
      printf("Number: %s\n", n->number);
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

  while (n != NULL)
  {
    n = n->next;
    counter++;
  }
  return counter;
}
