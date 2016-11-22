#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct opt
{
  int e;
  int E;
  int n;
};

struct opt *update_options(char *word, struct opt *options)
{
  
  for (unsigned i = 1; i < strlen(word); ++i)
  {
    if (word[i] == 'n')
      options->n = 1;
    else if (word[i] == 'e')
    {
      options->e = 1;
      options->E = 0;
    }
    else if (word[i] == 'E')
    {
      options->e = 0;
      options->E = 1;
    }
  }
  return options;
}

void parse(char *arg)
{
  int begin = 0;
  int end = 0;
  char ptr = ' ';
  int size = strlen(arg);
  for (int i = 0; i < size; ++i)
  {
    if (arg[i] == '\'' || arg[i] == '\"')
    {
      if (ptr == ' ')
      {
        ptr = arg[i];
        begin = i;
      }
      else if (ptr == arg[i])
      {
        ptr = ' ';
        end = i;
        //each word
        for (int j = begin + 1; j < end; ++j)
        {
          putchar(arg[j]);
        }
        printf("\n");
      }
    }
  }
}
void echo(char *args[])
{
  struct opt *options = malloc(sizeof (struct opt));
  options->e = 0;
  options->E = 0;
  options->n = 0;
  char space[1] = {' '};
  int index = 0;
  char *arg = NULL;

  char *ptr = *args;
  while (ptr)
  {
    if (strcmp("./echo", ptr) == 0)
      printf("begin|");
    if (ptr[0] == '-' && arg)
      options = update_options(ptr, options);
    else
    {
      if (arg)
        arg = malloc(sizeof (char) * strlen(ptr));
      else
      { 
        arg = realloc(arg, sizeof(char) * (sizeof (arg) + sizeof (ptr) + 1));
        arg = strcat(arg, space);
      }
      arg = strcat(arg, ptr);
    }
    index++;
    ptr = args[index];
  }
  for (unsigned k = 0; k < 10; ++k)
    putchar(arg[k]);
  if (options->n == 0)
    printf("\n");
  printf("|fin: E=%d, e=%d, n=%d\n", options->E, options->e, options->n);
}

int main(void)
{
  //char *argv[4];
  //char *arg0 = "./echo";
  //char *arg1 = "-n";
  char *arg2 = "'esd\'\'fa'f";
  //argv[0] = arg0;
  //argv[1] = arg1;
  //argv[2] = arg2;
  //argv[3] = NULL;
  //echo(argv);
  parse(arg2);
  return 0;
}
