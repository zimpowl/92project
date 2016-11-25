#include "../include/tree.h"
#include "../include/parser.h"

int skip_line(void)
{
  int i = 0;
  do
  {
    char *token = take_token();
    if (token && strcmp(token, "\n") == 0)
    {
      valid_token();
      i++;
    }
    else
      return i;
  } while (1);

  return i;
}

int check_operators_p(void)
{
  char *token = take_token();
  if (!token)
    return 0;
  if (strcmp(token, "&") == 0 || strcmp(token, ";") == 0 
        || strcmp(token, "&&") == 0 || strcmp(token, "||") == 0
        || strcmp(token, "<") == 0 || strcmp(token, ">") == 0
        || strcmp(token, "<&") == 0 || strcmp(token, ">&") == 0
        || strcmp(token, "<>") == 0 || strcmp(token, "<<-") == 0
        || strcmp(token, "<>") == 0 || strcmp(token, "<<-") == 0
        || strcmp(token, ">|") == 0 || strcmp(token, "<<") == 0
        || strcmp(token, "(") == 0 || strcmp(token, ")") == 0
        || strcmp(token, "{") == 0 || strcmp(token, "}") == 0
        || strcmp(token, ">>") == 0 || strcmp(token, "|") == 0
        || strcmp(token, ";;") == 0 || strcmp(token, "\n") == 0)
    return 1;
  else
    return 0;
}

int check_reserved_p(void)
{
  char *token = take_token();
  if (token && ((strcmp(token, "if") == 0 || strcmp(token, "then") == 0 
        || strcmp(token, "else") == 0 || strcmp(token, "elif") == 0
        || strcmp(token, "fi") == 0 || strcmp(token, "do") == 0
        || strcmp(token, "done") == 0 || strcmp(token, "case") == 0
        || strcmp(token, "esac") == 0 || strcmp(token, "while") == 0
        || strcmp(token, "until") == 0 || strcmp(token, "for") == 0)))
    return 1;
  return 0;
}

struct ntree *input_p(void)
{
  struct ntree *ntree = list_p();
  return ntree;
}
