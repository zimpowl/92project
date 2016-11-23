#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include "../include/tree.h"

int setenv(const char *name, const char *value, int overwrite);


int cd(char **args)
{
  int index = 0;
  char *ptr = args[0];
  while (ptr)
  {

    if (strcmp(ptr, "cd") == 0)
    {

    }
    else if (ptr[0] == '-')
    {
      //options
    }
    else
    {
      add_word(0, "OLDPWD", search_word("PWD")->value);
      char *tmp = ptr;
      if (ptr[0] == '/')
      {
        add_word(0, "PWD", tmp);
      }
      else
      {
        char *value = malloc(sizeof (search_word("PWD")->value) * sizeof(char));
	value = search_word("PWD")->value;

        tmp = malloc(sizeof (ptr) + sizeof (value) + 1);
        
	//char slash[2] = {'/', '\0'};
	
	//tmp = strcat(value, slash);
	//tmp = strcat(tmp, ptr);
                
        chdir(tmp);
        setenv("PWD", tmp, 1);
	printf("%s\n", tmp);
        return 1;
      }
    }
    index++;
    ptr = args[index];
  }
  chdir(search_word("HOME")->value);
  print_words();
  
  return 0;
}

int main(void)
{
  init_env();
  char *argv[3];
  argv[0] = "cd";
  argv[1] = "hey";
  argv[2] = NULL;
  cd(argv);
  return 0;
}
