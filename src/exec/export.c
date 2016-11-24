#include <stdio.h>
#include <stdlib.h>
#include "../include/tree.h"

struct ops
{
  int n;
  int a;
}

int setenv(const char *name, const char *value, int overwrite);

int export(char **args)
{
  struct ops *options = malloc(sizeof (struct ops));
  int index = 1;
  while (args[index])
  {
    if (args[index][0] == '-')
    {
      for (int i = 1; i < strlen(args[index]))
      {
        if (args[index][i] == 'n')
          options->n = 1;
      }
    }
    else
    {
      for (int i = 1; i < strlen(args[index]))
      {
        if (args[index][i] == '=')
        {
          char *name = malloc(sizeof (char) * (i + 1));
          char *value = mallov(sizeof (char * (strlen(args[index]) - i + 1);
          name = strncpy(name, args[index], i + 1);
          value = strncpy(value, args[index],  strlen(args[index]) - i + 1));
          printf("name: %s\n", name);
          printf("value: %s\n", value);
          add_word(ENV_VAR, name, value);
          
      }
    }  
    setenv(name, value, 1);
    
    index++;
  }
  return 1;
}

int main(void)
{
  init_env();
  export("TEST", "okok");
  printf("%s\n", getenv("TEST"));
  return 0;
}
