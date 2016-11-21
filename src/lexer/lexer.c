#include "header_lexer.h"
#include <err.h>

char *g_line = NULL;
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
  if (!len)
    return;
  g_line = malloc(len * sizeof (char));
  if (!g_line)
    return;
  s[len] = '\0';
  g_line = strcpy(g_line, s);
  g_line[len] = '\0';
  g_list = take_1_token(0);
  if (g_list)
    g_list->next = take_1_token(g_list->i);
}

/*int main(int argc, char *argv[])
{
  if (argc != 2)
    errx(1, "nb argument : 1");
  init_lexer(argv[1]);
  char *s = take_token();
  while (s)
  {
    printf("%s\n", s);
    valid_token();
    s = take_token();
  }
}*/
