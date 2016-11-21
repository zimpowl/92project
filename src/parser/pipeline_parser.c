#include "../include/tree.h"
#include "../include/parser.h"

struct ntree *pipeline_p(void)
{
  struct ntree *ntree = NULL;

  char *token = take_token();
  if (token && strcmp(token, "!") == 0)
  {
    struct ntree *new_sep = new_ntree(token, PIPELINE);
    ntree = add_ntree(ntree, new_sep); 
    valid_token();
  }

  return pipeline_bis_p(ntree);
}

struct ntree *pipeline_bis_p(struct ntree *ntree)
{

  struct ntree *new = command_p();
  if (!new)
    return NULL;

  char *token = take_token();

  while (token && strcmp(token, "|") == 0)
  {
    valid_token();
    struct ntree *new_sep = new_ntree(token, PIPELINE);
    new_sep = add_ntree(new_sep, new);
    new = command_p();

    if (!new)
      return NULL;
    new_sep = add_ntree(new_sep, new);
    new = new_sep;
    token = take_token();
  }
  ntree = add_ntree(ntree, new);
  return ntree;
}
