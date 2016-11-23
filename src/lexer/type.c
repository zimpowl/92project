#include "header_lexer.h"

static int is_quoted1(const char c)
{
  return c == '\'';
}

static int is_dquoted1(const char c)
{
  return c == '\"';
}

static int is_operator1(const char *s)
{
  return s[0] == '&' || s[0] == ';' || s[0] == '<' || s[0] == '>' 
         || s[0] == '(' || s[0] == ')' || s[0] == '#' || s[0] == '\n'
         || s[0] == '|' || s[0] == '!' || s[0] == '{' || s[0] == '}';
}

static int is_operator2(const char *s)
{
  return !(strcmp(s, "&&") && strcmp(s, ";;") && strcmp(s, "<<") 
           && strcmp(s, ">>") && strcmp(s, "<&") && strcmp(s, ">&") 
           && strcmp(s, "<>") && strcmp(s, ">|") && strcmp(s, "||"));
}

static int is_operator3(const char *s)
{
  return !(strcmp(s, "<<-"));
}

int is_operator(char *tmp)
{
  size_t len = strlen(tmp);
  int res = 0;
  if (len == 1)
    res = is_operator1(tmp);
  else if (len == 2)
    res = is_operator2(tmp);
  else if (len == 3)
    res = is_operator3(tmp);
  return res;
}

int is_quoted(char *s, size_t len, enum type_token type)
{
  int res = is_quoted1(s[len - 2]/*s[len - 2]*/);
  if ((res && type != WORD_QUOTED) || (type == WORD_QUOTED && !res))
    return 1; //WORD_QUOTED;
  else if (res && type == WORD_QUOTED)
    return 2; //WORD;
  return 0;
}

int is_dquoted(char *s, size_t len, enum type_token type)
{
  int res = is_dquoted1(s[len - 2]) && s[len - 3] != '\\';
  if ((res && type != WORD_DQUOTED) || (type == WORD_DQUOTED && !res))
    return 1; //WORD_QUOTED;
  else if (res && type == WORD_DQUOTED)
    return 2; //WORD;
  return 0;
}

enum type_token take_type(char *s, char c, enum type_token type)
{
  char *tmp = append(s, c);
  size_t len = strlen(tmp);
  int res = 0;
  res = is_operator(tmp);
  free(tmp);
  if (res)
    return OPERATOR;
  else
  {
    res = is_quoted(s, len, type);
    if (res == 1)
      return WORD_QUOTED;
    else if (res == 2)
      return WORD;
    else
    {
      res = is_dquoted(s, len, type);
      if (res == 1)
        return WORD_DQUOTED;
      else
        return WORD;
    }
  }
  return WORD;
}
