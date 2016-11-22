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
  //else if (ntree->token == ASSIGNMENT_WORD)
    //i = assign_a(ntree);
  else if (ntree->token == RESERVED_WORD)
    i = rules_a(ntree);
  else if (ntree->token == PIPELINE)
    i = pipeline_a(ntree);
  return i;
}

/*int assign_a(struct ntree *ntree)
{
  return add_word(ntree->token, ntree->sons[0], ntree->sons[1]);
}*/

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
    bigtab[cnt - i] = malloc(sizeof (newcom->name));
    bigtab[cnt - i][0] = newcom->name;
    for (unsigned j = 0; j < newcom->size; j++)
    {
      bigtab[cnt - i][j + 1] = new->sons[j]->name;
    }
    bigtab[cnt - i][newcom->size + 1] = NULL;
    new = new->sons[0];
  }

  bigtab[0] = malloc(sizeof (new->name));
  bigtab[0][0] = new->name;
  for (unsigned j = 0; j < new->size; j++)
  {
    bigtab[0][j + 1] = new->sons[j]->name;
  }
  bigtab[0][new->size + 1] = NULL;
  bigtab[cnt + 1] = NULL;
  
  return exec_pipe(bigtab);
}
