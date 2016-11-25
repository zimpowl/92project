#include "../include/tree.h"
#include "../include/parser.h"
#include "../include/ast_reader.h"
#include "../include/executor.h"

int rules_a(struct ntree *ntree)
{
  if (strcmp(ntree->name, "if") == 0)
    return rule_if_a(ntree);
  if (strcmp(ntree->name, "elif") == 0)
    return rule_if_a(ntree);
  if (strcmp(ntree->name, "while") == 0)
    return rule_while_a(ntree);
  if (strcmp(ntree->name, "until") == 0)
    return rule_until_a(ntree);
  if (strcmp(ntree->name, "for") == 0)
    return rule_for_a(ntree);
  if (strcmp(ntree->name, "case") == 0)
    return rule_case_a(ntree);
  return 1;
}

int rule_if_a(struct ntree *ntree)
{
    int res = manage_a(ntree->sons[0]);
    if (res == 0)
      return manage_a(ntree->sons[2]);
    else if (strcmp(ntree->sons[3]->name, "elif") == 0)
      res = rule_if_a(ntree->sons[3]);
    else if (strcmp(ntree->sons[3]->name, "else") == 0)
      res = manage_a(ntree->sons[3]->sons[0]);
    return res;
}

int rule_while_a(struct ntree *ntree)
{
  while (manage_a(ntree->sons[0]) == 0)
  {
    if (do_group_a(ntree->sons[1]) != 0)
        return 1;
  }
  return 0;
}

int rule_until_a(struct ntree *ntree)
{
  while (manage_a(ntree->sons[0]) != 0)
  {
    if (do_group_a(ntree->sons[1]) != 0)
        return 1;
  }
  return 0;
}

int rule_for_a(struct ntree *ntree)
{
  int i = 2;
  for (; ntree->sons[i]->token != LIST; i++)
  {
    if (add_word(VAR, NULL,ntree->sons[0]->name, ntree->sons[i]->name))
      do_group_a(ntree->sons[ntree->size-1]);
  }
  return 0;
}

int rule_case_a(struct ntree *ntree)
{
  for (int i = 2; strcmp(ntree->sons[i]->name, "esac") != 0; i++)
  {
    int res = rule_caseitem_a(ntree->sons[i], ntree->sons[0]->name);
    if (res != -1)
      return res;
  }
  return 0;
}

int rule_caseitem_a(struct ntree *ntree, char *str)
{
  for (unsigned i = 0; i < ntree->size - 1; i++)
  {
    char *name = var_assigned_a(ntree->sons[i]->name);
    char *value = var_assigned_a(str);
    if (strcmp(name, value) == 0)
      return manage_a(ntree->sons[ntree->size-1]);
  }
  return -1;
}

int do_group_a(struct ntree *ntree)
{
  return manage_a(ntree->sons[0]);
}
