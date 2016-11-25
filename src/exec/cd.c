#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "../include/tree.h"
#include "../include/executor.h"

int setenv(const char *name, const char *value, int overwrite);
int lstat(const char *restrict path, struct stat *restrict buf);

int is_dir(char *path)
{
  DIR *dir = opendir(path);
  if (dir)
    return 1;
  return 0;
}

int change_cd(char *res)
{
  struct word *pwd = search_word("PWD");
  struct word *oldpwd = search_word("OLDPWD");
  if (!pwd)
    return 1;
  free(oldpwd);
  oldpwd->value = pwd->value;
  setenv("OLDPWD", oldpwd->value, 1);
  free(pwd->value);
  pwd->value = res;
  setenv("PWD", pwd->value, 1);
  chdir(res);
  //printf("pwd: %s\n", pwd->value);
  return 0;
}

int cd_home(void)
{
  struct word *home =search_word("HOME");
  if (!home->value || !is_dir(home->value))
    return 0;
  return change_cd(home->value);
}

int cd_prev(void)
{
  struct word *oldpwd = search_word("OLDPWD");
  if (!oldpwd->value)
  {
    printf("\n");
    return 1;
  }
  if (!is_dir(oldpwd->value))
  {
    printf("« OLDPWD » not defined\n");
    return 1;
  }
  return change_cd(oldpwd->value);
}

int cd_dotdot(void)
{
  struct word *pwd = search_word("PWD");
  int tmp = 0;
  for (unsigned i = 0; i < strlen(pwd->value); ++i)
  {
    if (pwd->value[i] == '/')
      tmp = i;
  }
  char *res = malloc(sizeof (char) * tmp + 1);
  memcpy(res, pwd->value, tmp);
  res[tmp] = '\0';
  return change_cd(res);
}
  

char *get_path(char *s1, char *s2)
{
  char *ts1 = malloc(strlen(s1) * sizeof (char) + 1);
  memcpy(ts1, s1, strlen(s1) * sizeof (char));
  ts1[strlen(s1) * sizeof (char)] = '\0';
  char *ts2 = malloc(strlen(s2) * sizeof (char) + 1);
  memcpy(ts2, s2, strlen(s2));
  s2[strlen(s2) * sizeof (char)] = '\0';
  char *res = malloc(strlen(s1) + strlen(ts2) + 2);
  char *slash = malloc(sizeof (char) * 2);
  slash[0] = '/';
  slash[1] = '\0';
  strcpy(res, ts1);
  strcat(res, slash);
  strcat(res, ts2);
  free(ts1);
  free(ts2);
  free(slash);
  ts1 = NULL;
  ts2 = NULL;  
  return res;
}

int speccases(char *arg)
{
  if (!arg)
    return cd_home();
  if (strcmp(arg, ".") == 0)
  {
    struct word *pwd = search_word("PWD");
    struct word *oldpwd = search_word("OLDPWD");
    if (strlen(oldpwd->value) > 0)
    free(oldpwd->value);
    oldpwd->value = malloc(strlen(pwd->value) + 1);
    strcpy(oldpwd->value ,pwd->value);
    oldpwd->value[strlen(oldpwd->value)] = '\0';
    setenv("OLDPWD", oldpwd->value, 1);
    return 0;
  }
  if (strcmp(arg, "~") == 0)
    return cd_home();
  if (strcmp(arg, "-") == 0)
    return cd_prev();
  if (strcmp(arg, "..") == 0)
      return cd_dotdot(); 
  return -2;
}

int my_cd(char **args)
{
  int index = 1;
  char *res = NULL;
  int check = speccases(args[index]);
  if (check != -2)
    return check;
  while (args[index])
  {
    if (args[index][0] != '-')
    {
      if (args[index][0] == '/')
        res = args[index];
      else
        res = get_path(search_word("PWD")->value, args[index]);
      if (is_dir(res))
        return change_cd(res);
      return 1;
    }
    index++;
  }
  return 0;
}

/*int main(void)
{
  init_environment();
  char *argv[2];
  argv[0] = "cd";
  char *tmp = malloc(sizeof (char) * 4);
  tmp[0] = 'f';
  tmp[1] = 'o';
  tmp[2] = 'o';
  tmp[3] = '\0';
  argv[1] = tmp;
  argv[2] = NULL;
  printf("PWD: %s\n", getenv("PWD"));
  printf("OLDPWD: %s\n", getenv("OLDPWD"));
  int res =my_cd(argv);
  printf("PWD: %s\n", getenv("PWD"));
  printf("OLDPWD: %s\n", getenv("OLDPWD"));
  destroy_words();
  return res;
}*/
