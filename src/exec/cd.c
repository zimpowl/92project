#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include "../include/tree.h"
#include <dirent.h>

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
    
    }  
  }
  
  print_words();
  
  return 0;
}


int main(void)
{
  chdir("/home/dany/");
  putenv("PWD=/");
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
