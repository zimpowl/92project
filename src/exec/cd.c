#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "../include/tree.h"

struct ops
{
  int a;
  int e;
};

int setenv(const char *name, const char *value, int overwrite);
int lstat(const char *restrict path, struct stat *restrict buf);

int is_dir(char *path)
{
  DIR *dir = opendir(path);
  if (dir)
  {
 //   closedir(dir);
    return 1;
  }
 // closedir(dir);
  return 0;
}

int cd(char **args)
{
  int index = 0;
  char *ptr = args[1];
  char *res = NULL;
  while (ptr)
  {
    if (ptr[0] == '-')
    {
      //for (int i = 1)
    }
    else
    {
      if (ptr[0] == '/')
        res = ptr;
      else
      {
        char *value = search_word("PWD")->value;

        res = malloc(sizeof (ptr) + sizeof (value) + 1);
	strcpy(res, value);
        printf("value: %s\n", value);
	res = strcat(res, "/");
        printf("res0: %s\n", res);
	res = strcat(res, ptr);
        printf("res1: %s\n", res);
      }
      break;
    }
    index++;
    ptr = args[index];
  }
  //char *tmp = malloc(sizeof (res));
  //strncpy(tmp, res, strlen(res));
  //printf("tmp: %s\n", tmp);
  if (1)
  {
    printf("res: %s\n", res);
    
    add_word(0, "OLDPWD", search_word("PWD")->value);
    add_word(0, "PWD", res);
    chdir(res);
    setenv("OLDPWD", search_word("OLDPWD")->value, 1);
    setenv("PWD", res, 1);
    return 0;
  }
  else
    return 1;
}

int main(void)
{
  //if (argc < 2)
    //return 1;
  init_env();
  char *argv[3];
  argv[0] = "cd";
  argv[1] = "foo";
  argv[2] = NULL;
  printf("first PWD: %s\n", search_word("PWD")->value);
  printf("first OLDPWD: %s\n", search_word("OLDPWD")->value);
  int res =cd(argv);
  printf("PWD: %s\n", search_word("PWD")->value);
  printf("OLDPWD: %s\n", search_word("OLDPWD")->value);
  destroy_words();
  return res;
}
