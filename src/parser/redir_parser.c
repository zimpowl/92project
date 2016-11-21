#include "../include/tree.h"
#include "../include/parser.h"

struct ntree *redir_p(void)
{
  struct ntree *ntree = NULL;
  struct ntree *new = NULL;
  char *token = take_token();
  char *token2 = take_next_token();
  if (check_redir(token2) == 1)
  {
    ntree = new_ntree(token2, REDIRECTION);
    if (check_ionumber(token) <= 0)
      return NULL;
    new = new_ntree(token, IO_NUMBER);
    ntree = add_ntree(ntree, new);
    valid_token();
  }
  else if (check_ionumber(token) == 1)
    ntree = new_ntree(token, REDIRECTION);
  else
    return NULL;
  valid_token();
  token = take_token();
  if (!token)
    return NULL;
  valid_token();
  new = new_ntree(token, WORD);
  ntree = add_ntree(ntree, new);
  return ntree;
}

int check_redir(char *tok)
{
  if (tok && (strcmp(tok, ">") == 0 || strcmp(tok, "<") == 0
      || strcmp(tok, ">>") == 0 || strcmp(tok, "<<") == 0
      || strcmp(tok, "<<-") == 0 || strcmp(tok, ">&") == 0
      || strcmp(tok, "<&") == 0 || strcmp(tok, ">|") == 0
      || strcmp(tok, "<>") == 0))
    return 1;
  return 0;
}

int check_ionumber(char *tok)
{
  int i = 0;
  if (!tok)
    return i;
  for (; tok[i]; i++)
  {
    if (tok[i] < '0' || tok[i] > '9')
      return 0;
  }
  return i;
}
