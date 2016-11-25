#include "../include/tree.h"
#include "../include/parser.h"
#include "../include/ast_reader.h"
#include "../include/executor.h"

int read_a(struct ntree *ntree)
{
  int res = manage_a(ntree);
  free_ast(ntree);
  if (res == 0)
    return 0;
  return res;
}

void free_ast(struct ntree *ntree)
{
  if (!ntree)
    return;
  for (unsigned i = 0; i < ntree->size; i++)
  {
    free_ast(ntree->sons[0]);
  }
  free(ntree);
}

int manage_a(struct ntree *ntree)
{
  int i = 1;
  if (!ntree)
    return i;
  else if (ntree->token == LIST)
    i = list_a(ntree);
  else if (ntree->token == AND_OR)
    i = and_or_a(ntree);
  else if (ntree->token == COMMAND)
    i = command_a(ntree);
  else if (ntree->token == RESERVED_WORD)
    i = rules_a(ntree);
  else if (ntree->token == PIPELINE)
    i = pipeline_a(ntree);
  else if (ntree->token == FUNCTION)
    i = reg_func_a(ntree);
  return i;
}

int list_a(struct ntree *ntree)
{
  int i = 0;
  int j = 0;
  if (strcmp(ntree->name, ";") == 0 || strcmp(ntree->name, "&") == 0)
  {
    i = manage_a(ntree->sons[0]);
    if (ntree->size > 1)
      j = manage_a(ntree->sons[1]);
    if (i == 0 && j == 0)
      return 0;
  }
  return i;
}

int and_or_a(struct ntree *ntree)
{
  if (strcmp(ntree->name, "&&") == 0)
  {
    int res = manage_a(ntree->sons[0]);
    if (res == 0)
      return manage_a(ntree->sons[1]);
    else
      return res;
  }
  else if (strcmp(ntree->name, "||") == 0)
  {
    int res = manage_a(ntree->sons[0]);
    if (res == 0)
      return res;
    else
      return manage_a(ntree->sons[1]);
  }
  else
    return 1;
}

int check_assign_a(struct ntree *ntree)
{
  char *str = ntree->name;
  unsigned i = 0;
  for (; i < strlen(str); i++)
  {
    if (str[i] ==  '=' && str[i+1])
    { 
      if (str[i+1] == '=')
        return -1;
      else
        break;
    }
  }
  if (i >= strlen(str))
    return -1;
  char *name = strtok(str, "=");
  char *value = strtok(NULL, "\0");
  int res = add_word(VAR, NULL, name, value);
  if (res == 1)
    return 0;
  else return 1;
}

int check_condition_a(struct ntree *ntree)
{
  char *str = ntree->name;
  unsigned i = 0;
  for (; i < strlen(str); i++)
  {
    if (str[i] == '=' && str[i+1] 
        && str[i+1] == '=' && str[i+2] 
          && str[i+2] != '=')
    {
      char *name = strtok(str, "==");
      char *value = strtok(NULL, "=");
      struct word *w = search_word(name);
      if (!w)
        return -1;

      if (strcmp(w->value, value) == 0)
        return 0;
      return 1;
    }
  }
  return -1;
}

int check_func_a(char *name)
{
  struct word *w = search_word(name);
  if (w && w->token == FUNCTION)
  {
    return manage_a(w->ntree);
  }
  return -1;
}

char *var_assigned_a(char *name)
{
  if (strstr(name, "$") == NULL)
    return name;

  char *n = strtok(name, "$");
  struct word *w = search_word(n);
  if (!w)
    return name;

  return w->value;
}


int command_a(struct ntree *ntree)
{
  int res = check_assign_a(ntree);
  if (res != -1)
    return res;
  
  res = check_condition_a(ntree);
  if (res != -1)
    return res;

  res = check_func_a(ntree->name);
  if (res != -1)
    return res;

  char *command[ntree->size + 2];
  command[0] = ntree->name;
  for (unsigned i = 0; i < ntree->size; i++)
    command[i+1] = var_assigned_a(ntree->sons[i]->name);
  
  command[ntree->size + 1] = NULL;
  return exec(command);
}

int pipeline_nor_a(struct ntree *ntree)
{
  if (strcmp(ntree->name, "!") != 0)
    return -1;

  int res = manage_a(ntree->sons[0]);
  if (res == 0)
    return 1;
  else
    return 0;
}

int pipeline_a(struct ntree *ntree)
{
  struct ntree *new = ntree;
  int cnt = 0;

  int check_nor = pipeline_nor_a(ntree);
  if (check_nor != -1)
    return check_nor;

  while (new && new->token == PIPELINE)
  {
    cnt ++;
    new = new->sons[0];
  }

  new = ntree;
  char **bigtab[cnt + 2];
  for (int i = 0; i < cnt; i++)
  {
    struct ntree *newcom = new->sons[1];
    bigtab[cnt - i] = malloc(sizeof (newcom->name) * 5);
    bigtab[cnt - i][0] = newcom->name;
    for (unsigned j = 0; j < newcom->size; j++)
    {
      //bigtab[cnt - i] = realloc(bigtab[0], sizeof (new->name) * sizeof (new->sons[j]->name));
      bigtab[cnt - i][j + 1] = newcom->sons[j]->name;
    }
    bigtab[cnt - i][newcom->size + 1] = NULL;
    new = new->sons[0];
  }

  bigtab[0] = malloc(sizeof (new->name) * 5);
  bigtab[0][0] = new->name;
  for (unsigned j = 0; j < new->size; j++)
  {
    //bigtab[0] = realloc(bigtab[0], sizeof (new->name) * sizeof (new->sons[j]->name));
    bigtab[0][j + 1] = new->sons[j]->name;
  }
  bigtab[0][new->size + 1] = NULL;
  bigtab[cnt + 1] = NULL;
  
  return exec_pipe(bigtab);
}
