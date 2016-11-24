#include "../include/tree.h"
#include "../include/parser.h"

struct ntree *func_p(void)
{
  func_bis_p();
  char *token = take_token();
  char *token2 = take_next_token();
  if (!token2 || strcmp(token2, "(") != 0)
      return NULL;
  valid_token();
  struct ntree *ntree = new_ntree(token, FUNCTION);
  token = take_token();
  valid_token();
  token = take_token();
  if (!token || strcmp(token, ")") != 0)
    return NULL;
  valid_token();
  return func_bisbis_p(ntree);
}

void func_bis_p(void)
{
  char *token = take_token();
  if (token && strcmp(token, "function") == 0)
    valid_token();
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
