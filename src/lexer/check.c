#include "header_lexer.h"

static size_t search_quoted(char *s)
{
  size_t i = strlen(s) - 2;
  for(; s[i] != '\''; i--)
    continue;
  return i;
}

static void delete_quoted(struct list_token *list, size_t quote)
{
    size_t len = strlen(list->token.s);
    my_delete(list->token.s, len - quote);
    my_delete(list->token.s, search_quoted(list->token.s));
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
