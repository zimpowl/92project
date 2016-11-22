#include "header_lexer.h"

int search_dquoted(char *s, int start)
{
  int i = strlen(s) - 1;
  if (!start)
  {
    for(; i >= 0 && s[i] != '\"' && s[i - 1] == '\\'; i--)
      continue;
    //i++;
  }
  else
  {
    i = 0;
    for(; s[i] != '\0' && s[i] != '\"' && s[i - 1] == '\\'; i++)
      continue;
    //i--;
  }
  
  return i;
}

int search_quoted(char *s, int start)
{
  int i = strlen(s) - 1;
  if (!start)
  {
    for(; s[i] != '\'' && i >= 0; i--)
      continue;
    //i++;
  }
  else
  {
    i = 0;
    for(; s[i] != '\'' && s[i] != '\0'; i++)
      continue;
    //i--;
  }
  
  return i;
}

static void delete_quoted(struct list_token *list, size_t quote)
{
    size_t len = strlen(list->token.s);
    list->token.s = my_delete(list->token.s, len - quote);
    list->token.s = my_delete(list->token.s, search_quoted(list->token.s, 0));
    len = strlen(list->token.s);
    list->token.s[len] = '\0';
}

void check_delete_end(struct list_token *list)
{
  if (list->token.type == WORD_QUOTED)
  {
    delete_quoted(list, 1);
  }
}

void check_delete(enum type_token type, struct list_token *list)
{
  if (list->token.type != WORD_QUOTED && type == WORD_QUOTED)
  {
    delete_quoted(list, 2);
  }
}
