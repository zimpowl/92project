#include "header_lexer.h"

static int is_WORD(enum type_token type)
{
  return type == WORD_QUOTED || type == WORD || type == WORD_DQUOTED;
}

static size_t new_i(size_t i)
{
  while (g_line[i] == ' ' || g_line[i] == '\t')
    i++;
  if (g_line[i] == '#')
  {
    while (g_line[i] != '\n' && g_line[i] != '\0')
      i++;
  }
  return i;
}

struct token init_token(size_t i)
{
  struct token tok;
  tok.type = take_type("", g_line[i], WORD);
  if (g_line[i] != '\0')
  {
    tok.s = malloc(2 * sizeof (char));
    if (tok.s)
    {
      tok.s[0] = g_line[i];
      tok.s[1] = '\0';
    }
  }
  else
    tok.s = NULL;
  return tok;
}

int is_continue(struct token tok, size_t i)
{
  if ((tok.type == WORD_QUOTED || tok.type == WORD_DQUOTED) && 
      g_line[i] != '\0')
    return is_WORD(take_type(tok.s, g_line[i], tok.type));
  if (g_line[i] == ' ' || g_line[i] == '\n' || g_line[i] == '\0' 
      || g_line[i] == '\t')
    return 0;
  if (tok.type == OPERATOR)
    return take_type(tok.s, g_line[i], tok.type) == OPERATOR;
  else
    return is_WORD(take_type("", g_line[i], tok.type));
}

struct token new_token(struct token prev, size_t i)
{
  struct token res;
  res.type = take_type(prev.s, g_line[i], prev.type);
  res.s = append(prev.s, g_line[i]);
  return res;
}

struct list_token *init_list_token(size_t i)
{
  struct list_token *list = malloc(sizeof (struct list_token));
  if (!list)
    return NULL;
  list->next = NULL;
  i = new_i(i);
  list->token = init_token(i);
  if (list->token.s)
    list->i = i + 1;
  else
    list->i = i;
  return list;
}

struct list_token *take_1_token(size_t i)
{
  if (g_line[i] == '\0')
  {
    if (g_line)
      free(g_line);
    return NULL;
  }
  struct list_token *my_list = init_list_token(i);
  i = my_list->i;
  int cont = 0;
  do
  {
    cont = is_continue(my_list->token, i);
    if ((g_line[i] == ' ' || g_line[i] == '\t' /*|| g_line[i] == '\0'*/) 
         && my_list->token.type != WORD_QUOTED 
         && my_list->token.type != WORD_DQUOTED)
      i++;
    if (cont)
    {
      my_list->token = new_token(my_list->token, i);
      i++;
    }
  } while (cont);

  my_list->i = i;
  return my_list;
}
