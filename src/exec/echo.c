#include <../include/executor.h>
#include <../include/lexer.h>
#include <../include/tree.h>

struct string_i
{
  char *s;
  int i;
};

static struct string_i init_string(char *s, int i)
{
  struct string_i res;
  res.s = s;
  res.i = i;
  return res;
}

static struct string_i dolar(struct string_i S)
{
  int begin = S.i;
  S.s = my_delete(S.s, S.i);
  char *name = "";
  while (S.s[S.i] != '\0' && S.s[S.i] != '\'' && S.s[S.i] != '\"' 
         && S.s[S.i] != '\\')
  {
    name = append(name, S.s[S.i]);
    S.s = my_delete(S.s, S.i);
  }
  struct word *w = search_word(name);
  if (w)
    S.s = my_insert(S.s, w->value, begin);
  return S;
}

static struct string_i my_print_e(struct string_i S)
{
  printf("%.*s", S.i, S.s);
  int max = S.i;
  for (int i = 0; i < max; i++)
    S.s = my_delete(S.s, 0);
  S.i = 0;
  return S;
}

static struct string_i echo_e(char c, struct string_i S)
{
  S = my_print_e(S);
  if (c == 'n')
    printf("\n");
  else if (c == 't')
    printf("\t");
  else if (c == 'a')
    printf("\a");
  else if (c == 'b')
    printf("\b");
//  else if (c == 'c')
//    printf("\c");
//  else if (c == 'e')
 //   printf("\e");
  else if (c == 'f')
    printf("\f");
  else if (c == 'r')
    printf("\r");
 else if (c == 'v')
    printf("\v");
 S.s = my_delete(S.s, S.i);
 S.s = my_delete(S.s, S.i);
 return S;
}

static struct string_i in_quoted(struct string_i S, int e)
{
  int begin = S.i;
  S.s = my_delete(S.s, begin);
  while (S.s[S.i] != '\'')
  {
    if (S.s[S.i] == '\\' && e)
    {
      S = echo_e(S.s[S.i + 1], S);
    }
    else
      S.i++;
  }
  S.s = my_delete(S.s, S.i);
  return S;
}

static struct string_i in_dquoted(struct string_i S, int e)
{
  int begin = S.i;
  S.s = my_delete(S.s, begin);
  while (S.s[S.i] != '\"')
  {
    if (S.s[S.i] == '$')
      S = dolar(S);
    else if (S.s[S.i] == '\\' 
             && (S.s[S.i + 1] == '\"' || S.s[S.i + 1] == '\\'))
    {
      S.s = my_delete(S.s, S.i);
      S.i++;
    }
    else if (S.s[S.i] == '\\' && e)
    {
      S = echo_e(S.s[S.i + 1], S);
    }
    else
      S.i++;
  }
  S.s = my_delete(S.s, S.i);
  return S;
}

struct string_i echo_one(struct string_i S, int e)
{
  while (S.s[S.i] != '\0')
  {
    if (S.s[S.i] == '$')
      S = dolar(S);
    else if (S.s[S.i] == '\'')
      S = in_quoted(S, e);
    else if (S.s[S.i] == '\\')
    {
      S.s = my_delete(S.s, S.i);
      S.i++;
    }
    else if (S.s[S.i] == '\"')
      S = in_dquoted(S, e);
    else
      S.i++;
  }
  return S;
}

static void echo_not_e(int argc, char *args[], int e)
{
  char *s = args[argc + 1];
  if (!s)
    return;
  struct string_i S = init_string(s, 0);
  S = echo_one(S, e);
  printf("%s", S.s);
  for (int i = argc + 2; args[i]; i++)
  {
    S = init_string(args[i], 0);
    S = echo_one(S, e);
    printf(" %s", S.s);
  }
}

static int echo_arg(int n, int e, int argc, char *args[])
{
  echo_not_e(argc, args, e);
  if (!n)
    printf("\n");
  return 0;
}

int my_echo(char *args[])
{
  int n = 0;
  int e = 0;
  int argc = 0;
  int b = 1;
  for (int i = 1; args[i] && args[i][0] == '-' && b; i++)
  {
    switch (args[i][1])
    {
    case 'e':
      e = 1;
      break;
    case 'E':
      e = 0;
      break;
    case 'n':
      n = 1;
      break;
    default:
      argc--;
      b = 0;
      break;
    }
    argc++;
  }
  return echo_arg(n, e, argc, args);
}
