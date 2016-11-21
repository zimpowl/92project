#include "../include/tree.h"
#include "../include/parser.h"

struct ntree *func_p(void)
{
  struct ntree *ntree = func_bis_p();
  char *token = take_token();
  char *token2 = take_next_token();
  if (!token2 || strcmp(token2, "(") != 0)
    return NULL;
  valid_token();
  struct ntree *new = new_ntree(token, WORD);
  ntree = add_ntree(ntree, new);
  token = take_token();
  valid_token();
  new = new_ntree(token, FUNCTION);
  ntree = add_ntree(ntree, new);
  token = take_token();
  if (!token || strcmp(token, ")") != 0)
    return NULL;
  new = new_ntree(token, FUNCTION);
  ntree = add_ntree(ntree, new);
  return func_bisbis_p(ntree);
}

struct ntree *func_bis_p(void)
{
  struct ntree *ntree = NULL;
  char *token = take_token();
  if (token && strcmp(token, "function") == 0)
  {
    valid_token();
    ntree = new_ntree(token, FUNCTION);
  }
  return ntree;
}

struct ntree *func_bisbis_p(struct ntree *ntree)
{
  skip_line();
  struct ntree *new = shell_command_p();
  if (!new)
    return NULL;
  ntree = add_ntree(ntree, new);
  return ntree;
}
