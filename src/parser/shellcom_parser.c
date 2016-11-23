#include "../include/tree.h"
#include "../include/parser.h"

struct ntree *shell_command_p(void)
{
  struct ntree *new = rule_if_p();
  if (new)
    return new;

  new = rule_whiletil_p();
  if (new)
    return new;
  
  new = rule_for_p();
  if (new)
    return new;

  new = shell_commandbis_p();
  return new;
}

struct ntree *shell_commandbis_p(void)
{
  char *token = take_token();
  struct ntree *new = NULL;
  if (token && strcmp(token, "{") == 0)
  {
    valid_token();
    new = compound_list_p();
    if (!new)
      return NULL;
    token = take_token();
    if (token && strcmp(token, "}") != 0)
      return NULL;
    valid_token();
  }
  else if (token && strcmp(token, "(") == 0)
  {
    valid_token();
    new = compound_list_p();
    if (!new)
      return NULL;
    token = take_token();
    if (token && strcmp(token, ")") != 0)
      return NULL;
    valid_token();
  }
  return new;
}
