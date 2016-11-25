#include "../include/tree.h"
#include "../include/parser.h"

struct ntree *list_p(void)
{
  struct ntree *new = and_or_p();
  if (!new)
    return NULL;

  char *token = take_token();

  while (token && (strcmp(token, ";") == 0
      || strcmp(token, "&") == 0))
  {
    valid_token();
    struct ntree *new_sep = new_ntree(token, LIST);
    new_sep = add_ntree(new_sep, new);
    new_sep = add_ntree(new_sep, and_or_p());

    new = new_sep;
    token = take_token();
  }
  return new;
}

struct ntree *compound_list_p(void)
{
  skip_line();
  
  struct ntree *new = and_or_p();
  if (!new)
    return NULL;
  
  char *token = take_token();
  while (token && (strcmp(token, ";") == 0 || strcmp(token, "&") == 0
        || strcmp(token, "\n") == 0))
  {
    struct ntree *new_sep = new_ntree(";", LIST);
    valid_token();

    skip_line();
    new_sep = add_ntree(new_sep, new);
    new = and_or_p();
    if (new)
      new_sep = add_ntree(new_sep, new);
    new = new_sep;
    token = take_token();
  }
  //skip_line();
  return new;
}

struct ntree *do_group_p(void)
{
  char *token = take_token();
  
  if (!token || strcmp(token, "do") != 0)
    return NULL;

  valid_token();
  struct ntree *ntree = new_ntree(token, GROUP);
  struct ntree *new = compound_list_p();
  if (!new)
    return NULL;

  ntree = add_ntree(ntree, new);

  token = take_token();
  if (!token || strcmp(token, "done") != 0)
    return NULL;

  valid_token();
  new = new_ntree(token, GROUP);
  ntree = add_ntree(ntree, new);

  return ntree;
}
