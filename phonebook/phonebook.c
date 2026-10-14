#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../v2_linked_list/v2_linked_list.h"

node *contact_list[26];

void add_contact(void);
int hash(char *name);
void find_contact(char *name);
void print_list(void);
void remove_contact(char *name);
bool list_empty(void);


int main(void)
{
  for (int i = 0; i <= 26; i++)
  {
    contact_list[i] = NULL;
  }
  while (true)
  {
    char command = toupper(get_char("(A)dd Contact\n(D)elete contact\n(F)ind contact\n(S)how contact list\n(E)xit\nCommand: "));
    if (command == 'E')
    {
      for (int i = 0; i <= 26; i++)
      {
        if (contact_list[i] != NULL)
          free_list(contact_list[i]);
      }
      break;
    }
    
    switch (command)
    {
      case 'A':
        add_contact();
        break;
      case 'D':
        remove_contact(get_string("Name: "));
        break;
      case 'F':
        system("clear");
        find_contact(get_string("Name: "));
        break;
      case 'S':
        system("clear");
        print_list();
        break;
    }
  }
}

void add_contact()
{
  node new_contact;
  new_contact.name = get_string("Name: ");
  new_contact.number = get_string("Number: ");
  int name_hash = hash(new_contact.name);
  contact_list[name_hash] = append(&(contact_list[name_hash]), new_contact);
}

int hash (char *name)
{
  return tolower(name[0]) - 97;
}

void find_contact(char *name)
{
  node *contact = find(contact_list[hash(name)], name);
  if (contact == NULL)
  {
    printf("Contact %s not found.\n", name);
    return;
  }
    
  printf("Name: %s\n", contact->name);
  printf("Number: %s\n", contact->number);
  return;
}

void print_list()
{
  if (list_empty())
  {
    printf("List empty\n");
    return;
  }
  for (int i = 0; i <= 26; i++)
  {
    if (contact_list[i] != NULL)
    {
      printf("### %c ###\n", toupper(i + 97));
      printf("---------\n");
      show(contact_list[i]);
      printf("---------\n");
    }
  }
}

void remove_contact(char *name)
{
  if (delete(&(contact_list[hash(name)]), name))
  {
    printf("Success\n");
    return;
  }
  printf("Fail\n");
}

bool list_empty()
{
  for (int i = 0; i <= 26; i++)
  {
    if (contact_list[i] != NULL)
      return false;
  }
  return true;
}