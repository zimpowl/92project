#include "../include/tree.h"
#include "../include/parser.h"

struct ntree *command_p(void)
{
  struct ntree *new = shell_command_p();

  if (!new)
    new = func_p();

  if (new)
  {
    struct ntree *new_sep = NULL;
    do
    {
      new_sep = redir_p();
      new = add_ntree(new, new_sep);
    } while (new_sep);

  }
  else
    new = simple_command_p();

  return new;
}

struct ntree *simple_command_p(void)
{
  struct ntree *new = NULL;//prefix_p();
  struct ntree *new_sep = NULL;

  if (new)
  {
    do
    {
      struct ntree *new_sep = NULL;//prefix_p();
      new = add_ntree(new, new_sep);
    } while (new_sep);
  }

  do
  {
    new_sep = element_p();
    if (!new_sep)
      return new;
    new = add_ntree(new, new_sep);
  } while (new);

  return new;
}

/*struct ntree *prefix_p(void)
{
  char *token = take_token();
  char *token2 = take_next_token();
  struct ntree *ntree = NULL;

  if (token && token2 && strcmp(token2, "=") == 0)
  {
    valid_token();
    valid_token();
    ntree = new_ntree(token2, ASSIGNMENT_WORD);
    struct ntree *new = new_ntree(token, NAME);
    ntree = add_ntree(ntree, new);

    token = take_token();
    if (!token)
      return NULL;

    new = new_ntree(token, WORD);
    ntree = add_ntree(ntree, new);
    valid_token();
    return ntree;
  }
  else
    ntree = redir_p();

  return ntree;
}*/

struct ntree *element_p(void)
{
  char *token = take_token();
  if (!token || check_operators_p() == 1 || check_reserved_p() == 1)
    return redir_p();

  struct ntree *new = new_ntree(token, COMMAND);
  valid_token();
  token = take_token();

  while (token && check_operators_p() == 0 && check_reserved_p() == 0)
  {
    struct ntree *args = new_ntree(token, WORD);
    new = add_ntree(new, args);
    valid_token();
    token = take_token();
  }
  return new;
}
