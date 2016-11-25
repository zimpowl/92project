#include "header_lexer.h"

char *append(char *s, char c)
{
  size_t len = strlen(s);
  char *res = malloc((len + 2) * sizeof (char));
  if (!res)
    return NULL;
  res[0] = '\0';
  res = strcpy(res, s);
  res[len] = c;
  res[len + 1] = '\0';
  return res;
}

char *my_insert(char *s1, char *s2, int n)
{
  if (!strlen(s1))
    return s2;
  int len = strlen(s1) + strlen(s2);
  char *res = malloc((len + 1)* sizeof (char));
  if (!res)
    return NULL;
  int i = 0;
  for (i = 0; i < n; i++)
    res[i] = s1[i];
  int i1 = i;
  int len2 = strlen(s2);
  for (int i2 = 0; i2 < len2; i2++ , i++)
    res[i] = s2[i2];
  for (; i < len; i++ , i1++)
    res[i] = s1[i1];
  res[len] = '\0';
 // free(s1);
  return res;
}

char *my_delete(char *s, int n)
{
  int len = strlen(s);
  char *res = malloc(len * sizeof (char));
  if (!res)
    return NULL;
  int i = 0;
  for (i = 0; i < n; i++)
    res[i] = s[i];
  for (; i < len - 1; i++)
    res[i] = s[i + 1];
  res[len - 1] = '\0';
  free(s);
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
