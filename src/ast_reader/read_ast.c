#include "../include/tree.h"
#include "../include/parser.h"
#include "../include/ast_reader.h"
#include "../include/executor.h"

int read_a(struct ntree *ntree)
{
  int res = manage_a(ntree);
  if (res == 0)
    return 0;
  return res;
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
  return i;
}

int list_a(struct ntree *ntree)
{
  int i = 0;
  int j = 0;
  if (strcmp(ntree->name, ";") == 0 || strcmp(ntree->name, "&") == 0)
  {
    i = manage_a(ntree->sons[0]);
    j = manage_a(ntree->sons[1]);
    if (i == 0 || j == 0)
      return 0;
  }
  return (i + j);
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

int command_a(struct ntree *ntree)
{
  char *command[ntree->size + 2];
  command[0] = ntree->name;
  for (unsigned i = 0; i < ntree->size; i++)
    command[i+1] = ntree->sons[i]->name;
  command[ntree->size + 1] = NULL;
  return exec(command);
}

int pipeline_a(struct ntree *ntree)
{
  struct ntree *new = ntree;
  int cnt = 0;
  while (ntree->sons[0]->token == PIPELINE)
  {
    cnt ++;
    new = new->sons[0];
  }

  new = ntree;
  char **bigtab[cnt + 3];
  for (int i = 0; i < cnt; i ++)
  {
    char *tab[new->size + 2];
    tab[0] = new->name;
    tab[0] = malloc(sizeof (new->name) * sizeof(char));
    for (unsigned j = 0; j < new->size; j++)
    {
      tab[j + 1] = malloc(sizeof (new->sons[j]->name) * sizeof(char));
      tab[j + 1] = new->sons[j]->name;
    }
    tab[new->size + 1] = NULL;
    bigtab[i] = tab;
    new = new->sons[0];
  }
  
  struct ntree *newf = new->sons[0];
  char *tab[newf->size + 2]; 
  tab[0] = malloc(sizeof (newf->name) * sizeof(char));
  tab[0] = newf->name;
  for (unsigned l = 0; l < newf->size; l++)
  {
    tab[l + 1] = malloc(sizeof (newf->sons[l]->name) * sizeof (char));
    tab[l + 1] = newf->sons[l]->name;
  }
  tab[newf->size + 1] = NULL;
  
  newf = new->sons[1];
  char *tabb[newf->size + 2]; 
  tabb[0] = malloc(sizeof (newf->name) * sizeof(char));
  tabb[0] = newf->name;
  for (unsigned l = 0; l < newf->size; l++)
  {
    tabb[l + 1] = malloc(sizeof (newf->sons[l]->name) * sizeof (char));
    tabb[l + 1] = newf->sons[l]->name;
  }
  tabb[newf->size + 1] = NULL;
  
  bigtab[0] = tab;
  bigtab[1] = tabb;
  bigtab[2] = NULL;
  
  return exec_pipe(bigtab);
}

void print_bigtab(char **tab[])
{
  for (unsigned i = 0; tab[i] != NULL; i++)
  {
    for (unsigned j = 0; tab[i][j] != NULL; j++)
      printf("%s | ", tab[i][j]);
  }
}
