#include "header_lexer.h"

char *append(char *s, char c)
{
  size_t len = strlen(s);
  char *res = malloc((len + 1) * sizeof (char));
  if (!res)
    return NULL;
  res[0] = '\0';
  res = strcpy(res, s);
  res[len] = c;
  res[len + 1] = '\0';
  return res;
}

char *my_delete(char *s, size_t n)
{
  size_t len = strlen(s);
  char *res = malloc((len - 1) * sizeof (char));
  if (!res)
    return NULL;
  size_t i = 0;
  for (i = 0; i < n; i++)
    res[i] = s[i];
  for (; i < len - 1; i++)
    res[i] = s[i + 1];
 /*memmove(&s[i], &s[i + 1], len - i);
  s = realloc(s, (len - 1) * sizeof (char));
  s[len - 1] = '\0';*/
  res[len - 1] = '\0';
  //free(s);
  return res;
}

void delete_space(char *s)
{
  int b = 1;
  size_t len = strlen(s);
  size_t i = 0;
  for (size_t l = 0; l < len; l++)
  {
    if ((s[i] == ' ' || s[i] == '\t') && b)
    {
      my_delete(s, i);
    }
    else
    {
      if (s[i] == ' ' || s[i] == '\t')
        b = 1;
      else
        b = 0;
      i++;
    }
  }
}
