#define _GNU_SOURCE

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../v2_linked_list/v2_linked_list.h"

typedef node contact;

contact *contact_list[26];

void add_contact(char *name, char *number);
int hash(char *name);
contact create_contact(char *name, char *number);
void persist_to_file(void);
void load_from_file();
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
  load_from_file();
  return 0;
  while (true)
  {
    char command = toupper(get_char("(A)dd Contact\n(D)elete contact\n(F)ind contact\n(S)how contact list\n(E)xit\nCommand: "));
    if (command == 'E')
    {
      persist_to_file();
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
      add_contact(get_string("Name: "), get_string("Number: "));
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

void add_contact(char *name, char *number)
{
  contact new_contact = create_contact(name, number);
  int name_hash = hash(new_contact.name);
  contact_list[name_hash] = append(&(contact_list[name_hash]), new_contact);
}

contact create_contact(char *name, char *number)
{
  contact ctt;
  ctt.name = name;
  ctt.number = number;
  return ctt;
}

int hash (char *name)
{
  return tolower(name[0]) - 97;
}

void find_contact(char *name)
{
  contact *contact = find(contact_list[hash(name)], name);
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

void persist_to_file()
{
  FILE *db = fopen("phonebook.csv", "a");
  contact nd;
  for (int i = 0; i <= 26; i++)
  {
    if (contact_list[i] != NULL)
    {
      contact *lst = contact_list[i];
      while(lst != NULL)
      {
        fprintf(db, "%s,%s\n", lst->name, lst->number);
        lst = lst->next;
      }
    }
  }
  fclose(db);
}

void load_from_file()
{
  FILE *db = fopen("phonebook.csv", "r");
  size_t sz = 0;
  char *line = NULL;
  
  char *delim = malloc(1);
  *delim = 44;
  while(getline(&line, &sz, db) != -1)
  {
    // printf("%s", line);
    // char nl = '\n';
    char* name = strtok(line, delim);
    char* number = strtok(NULL, delim);
    if (number[strlen(number) - 1] == '\n')
      number[strlen(number) - 1] = '\0';
    // printf("Name: %s\n", name);
    // printf("Number: %s\n", number);
    // printf("%c\n", number[strlen(number) - 1]);
    add_contact(name, number);
  }
  print_list();
  fclose(db);
  free(delim);
  delim = NULL;
  free(line);
  line = NULL;
}