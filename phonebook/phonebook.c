#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../v2_linked_list/v2_linked_list.h"

node *contact_list[26];

void add_contact();
void print_list();
int hash(char *name);


int main(void)
{
  for (int i = 0; i <= 26; i++)
  {
    contact_list[i] = NULL;
  }
  while (true)
  {
    char command = toupper(get_char("(A)dd Contact\n(S)how contact list\n(E)xit\nCommand: "));
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

void print_list()
{
  for (int i = 0; i <= 26; i++)
  {
    if (contact_list[i] != NULL)
    {
      printf("### %c ###\n\n", toupper(i + 97));
      show(contact_list[i]);
    }
  }
}