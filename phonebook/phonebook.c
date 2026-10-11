#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../v2_linked_list/v2_linked_list.h"

node *list[26];

void add_contact(node *list, node contact);
int hash(char *name);


int main(void)
{
  
  while (true)
  {
    char command = get_char("(A)dd Contact\n(S)how contact list\n(E)xit\nCommand: ");
    if (command == 'E')
    break;
    
    switch (command)
    {
      node new_contact;
      case 'A':
        new_contact.name = get_string("Name: ");
        new_contact.number = get_string("Number: ");
        int name_hash = hash(new_contact.name);
        add_contact(list[name_hash], new_contact);
        system("clear");
        show(list[name_hash]);
        break;
    }
  }
}

void add_contact(node *list_per_first_letter, node contact)
{
  append(&list_per_first_letter, contact);

}

int hash (char *name)
{
  return tolower(name[0]) - 97;
}