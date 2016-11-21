#include "header_lexer.h"

char *g_line = '\0';
struct list_token *g_list = NULL;

char *take_token()
{
  if (g_list)
    return g_list->token.s;
  //free(g_line);
  return NULL;
}

char *take_next_token()
{
  if (g_list && g_list->next)
    return g_list->next->token.s;
  // free(g_line);
  return NULL;
}

void valid_token()
{
  if (!g_list)
    return;
  struct list_token *tmp = g_list;
  g_list = g_list->next;
  //free(tmp->token.s);
  free(tmp);
  if (!g_list)
    return;
  g_list->next = take_1_token(g_list->i);
}

void init_lexer(char *s)
{
  size_t len = strlen(s);
  g_line = malloc(len * sizeof (char));
  s[len] = '\0';
  g_line = strcpy(g_line, s);
  g_line[len] = '\0';
  g_list = take_1_token(0);
  g_list->next = take_1_token(g_list->i);
}
