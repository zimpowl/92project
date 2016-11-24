#include <stdio.h>
#include <stdlib.h>
#include "../include/executor.h"
#include "../include/tree.h"
int setenv(const char *name, const char *value, int overwrite);
int unsetenv(const char *name);

void print_rec(struct btree *btree)
{
  if (btree)
  {
    print_rec(btree->left);
    if (btree->word->token == ENV_VAR && strcmp(btree->word->value, "") != 0)
      printf("export %s=\"%s\"\n", btree->word->name, btree->word->value);
    else if (btree->word->token == ENV_VAR && strcmp(btree->word->value, "") == 0)
      printf("export %s\n", btree->word->name);
    print_rec(btree->right);
  }
}

int print(void)
{
  struct btree *btree = big_btree;
  print_rec(btree);
  return 0;
}

int add_delete(char *arg, int n)
{
  struct word *word = search_word(arg);
  if (!word)
    return 0;
  if (n && word->token == ENV_VAR)
  {
    unsetenv(word->name);
    word->token = VAR;
  }
  else if (word->token == VAR && !n)
  {
    setenv(word->name, word->value, 1);
    word->token = ENV_VAR;
  }
  return 0;
}

 
int add_assign(char *arg, int i)
{
  char *name = malloc(sizeof (char) * (i + 1));
  char *value = malloc(sizeof (char) * (strlen(arg) - i));
  name = strncpy(name, arg, i);
  value = strncpy(value, arg + i + 1,  (strlen(arg) - i - 1));
  add_word(ENV_VAR, name, value);
  setenv(name, value, 1);
  return 0;
}

int my_export(char **args)
{
  int n = 0;
  for (int index =1; args[index]; ++index)
  {
    if (args[index][0] == '-')
    {
      for (unsigned i = 1; i < strlen(args[index]); ++i)
      {
        if (args[index][i] == 'n')
          n = 1;
      }
    }
    else
    {
      for (unsigned i = 1; i < strlen(args[index]); ++i)
      {
        if (args[index][i] == '=' && n == 0)
          return add_assign(args[index], i);
      }
      return add_delete(args[index], n);
    }
  }
  return print();
}
