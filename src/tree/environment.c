#include <stdio.h>
#include <stdlib.h>
#include "../include/tree.h"


struct opt
{
  int a;
  int e;
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



int init_env(void)
{
  add_word(0, "HOME", getenv("HOME")); 
  add_word(0, "PWD", getenv("PWD")); 
  add_word(0, "OLDPWD", getenv("OLDPWD"));
  add_word(0, "IFS", getenv("IFS"));
  add_word(0, "PATH", getenv("PATH"));
  print_words();
  return 0;
}

int main(void)
{
  init_env();
  return 0;
}  
