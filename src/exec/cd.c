#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include "../include/tree.h"

int cd(char **args)
{
  char *ptr = args[1];
  struct word *tmp = search_word("PWD");
  while (ptr)
  {
    if (ptr[0] == '-')
    {
      //options
    }
    else
    {
      add_word(0, "OLDPWD", search_word("PWD")->value);
      chdir(ptr);
      setenv("PWD", ptr, 1);
      add_word(0, "PWD", 
      
    }  
  }
  chdir(search_word("HOME")->value);
  putenv("PWD=");
  
  print_words();
  
  return 0;
}

int setenv(const char *name, const char *value, int overwrite);
int main(void)
{
  init_env();
  chdir(".");
  setenv("PWD", search_word("PWD")->value, 1);
  printf("%s\n", getenv("PWD"));
  DIR           *d;
  struct dirent *dir;
  d = opendir(".");
  if (d)
  {
    while ((dir = readdir(d)) != NULL)
    {
      printf("%s\n", dir->d_name);
    }

    closedir(d);
  }
  return 0;
}
