#include "../include/tree.h"
#include "../include/parser.h"

struct ntree *rule_if_p(void)
{
 char *token = take_token();
  if (!token || strcmp(token, "if") != 0)
    return NULL;
  struct ntree *ntree = new_ntree(token, RESERVED_WORD);
  valid_token();
  
  struct ntree *new = compound_list_p();
  if (!new)
    return NULL;
  
  token = take_token();
  ntree = add_ntree(ntree, new);

  if (!token || strcmp(token, "then") != 0)
    return NULL;
  new = new_ntree(token, RESERVED_WORD);
  ntree = add_ntree(ntree, new);
  valid_token();
  return rule_fi_p(ntree);
}

struct ntree *rule_else_p(void)
{
  char *token = take_token();
  if (!token || strcmp(token, "elif") != 0)
    return rule_elseclause_p();
  valid_token();
  struct ntree *ntree = new_ntree(token, RESERVED_WORD);
  struct ntree *new = compound_list_p();
  if (!new)
    return NULL;
  ntree = add_ntree(ntree, new);
  token = take_token();
  if (!token || strcmp(token, "then") != 0)
    return NULL;
  valid_token();
  new = new_ntree(token, RESERVED_WORD);
  ntree = add_ntree(ntree, new);
  new = compound_list_p();
  if (!new)
    return NULL;
  ntree = add_ntree(ntree, new);
  new = rule_else_p();
  ntree = add_ntree(ntree, new);
  return ntree;
}

struct ntree *rule_elseclause_p(void)
{
  char *token = take_token();
  if (!token || strcmp(token, "else") != 0)
    return NULL;

  valid_token();
  struct ntree *ntree = new_ntree(token, RESERVED_WORD);
  struct ntree *new = compound_list_p();
  if (!new)
    return NULL;
  ntree = add_ntree(ntree, new);
  return ntree;
}

struct ntree *rule_fi_p(struct ntree *ntree)
{
  struct ntree *new = compound_list_p();
  if (!new)
    return NULL;
  ntree = add_ntree(ntree, new);
  new = rule_else_p();
  ntree = add_ntree(ntree, new);
  
  char *token = take_token();
  if (!token || strcmp(token, "fi") != 0)
    return NULL;
  new = new_ntree(token, RESERVED_WORD);
  ntree = add_ntree(ntree, new);
  valid_token();
  return ntree;
}

struct ntree *rule_whiletil_p(void)
{
  char *token = take_token();
  if (!token || 
      (token && strcmp(token, "while") != 0 && strcmp(token, "until") != 0))
    return NULL;

  valid_token();
  struct ntree *ntree = new_ntree(token, RESERVED_WORD);
  struct ntree *new = compound_list_p();
  if (!new)
    return NULL;

  ntree = add_ntree(ntree, new);
  new = do_group_p();
  if (!new)
    return NULL;

  ntree = add_ntree(ntree, new);
  return ntree;
}

struct ntree *rule_for_p(void)
{
  char *token = take_token();
  if (!token || strcmp(token, "for") != 0)
    return NULL;
  valid_token();
  struct ntree *ntree = new_ntree(token, RESERVED_WORD);
  token = take_token();
  if (!token)
    return NULL;
  valid_token();
  struct ntree *new = new_ntree(token, WORD);
  ntree = add_ntree(ntree, new);
  ntree = rule_forin_p(ntree);
  if (!ntree)
    return NULL;
  new = do_group_p();
  if (!new)
    return NULL;
  ntree = add_ntree(ntree, new);
  return ntree;
}

struct ntree *rule_forin_p(struct ntree *ntree)
{
  char *token = take_token();
  struct ntree *new = NULL;
  if (token && strcmp(token, ";") == 0)
  {
    valid_token();
    new = new_ntree(token, LIST);
    ntree = add_ntree(ntree, new);
    return ntree;
  }
  skip_line();

  token = take_token();
  if (!token || strcmp(token, "in") != 0)
    return NULL;
  valid_token();
  new = new_ntree(token, RESERVED_WORD);
  ntree = add_ntree(ntree, new);

  while (check_operators_p() == 0)
  {
    token = take_token();
    valid_token();
    new = new_ntree(token, WORD);
    ntree = add_ntree(ntree, new);
  }
  token = take_token();
  if (!token || (strcmp(token, ";") != 0 && strcmp(token, "\n") != 0))
    return NULL;
  valid_token();
  new = new_ntree(token, LIST);
  ntree = add_ntree(ntree, new);
  return ntree;
}

/*struct ntree *rule_case_p()
{
  char *token = take_token();
  if (!token || strcmp(token, "case") != 0)
    return NULL;
  valid_token();
  struct ntree *ntree = new_ntree(token, RESERVED_WORD);;
  token = take_token();
  if (!token)
    return NULL;
  valid_token();
  struct ntree *new = new_ntree(token, WORD);
  ntree = add_ntree(ntree, new);
  skip_line();
  token = take_token();
  if (!token || strcmp(token, "in") != 0)
    return NULL;
  valid_token();
  new = new_ntree(token, RESERVED_WORD);
  ntree = add_ntree(ntree, new);
  skip_line();
  return rule_caseclause_p(ntree);
}

struct ntree *rule_caseclause_p(struct ntree *ntree)
{
  struct ntree *new = rule_caseitem_p();
  ntree = add_ntree(
  char *token = take_token();
  
  do
  {
    if (strcmp(token, ";;") == 0)
    {
      valid_token();
      skip_line();
      
    }
  }
}

struct ntree *rule_caseitem_p()
{
  struct ntree *ntree = new_ntree("case_item", RESERVED_WORD);
  char *token = take_token();
  if (token && strcmp(token, "(") == 0)
  {
    valid_token();
    token = take_token();
  }
  
  struct ntree *new = new_ntree(token, WORD);
  ntree = add_ntree(ntree, new);
  
  token = take_token();
  while (token && strcmp(token, "|") != 0)
  {
    valid_token();
    token = take_token();
    if (!token)
      return NULL;
    valid_token();
    new = new_ntree(token, WORD);
    ntree = add_ntree(ntree, new);
    token = take_token();
  }

  if (token && strcmp(token, ")") != 0)
    return NULL;

  valid_token();
  skip_line();
  new = compound_list_a();
  ntree = add_ntree(ntree, new);
  return ntree;
}*/
