#include "io.h"

// int main(void)
// {
//   return 0;
// }
int get_int(char *prompt)
{
  printf("%s", prompt);
  int i;
  scanf("%i", &i);
  return i;
}

char get_char(char *prompt)
{
  printf("%s", prompt);
  char c;
  scanf("%c", &c);
  return c;
}