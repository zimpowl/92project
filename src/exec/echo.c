#include <../include/executor.h>
#include <../lexer/header_lexer.h>
//#include <../include/tree.h>

struct string_i
{
  char *s;
  int i;
};

static void echo_e(int argc, char *args[])
{
  printf("%s", args[argc + 1]);
  for (int i = argc + 2; args[i]; i++)
  {
    printf(" %s", args[i]);
  }
}

/*static struct string_i *in_dquoted(char *s, int end, int begin)
{
  for (int i = begin + 1; i < end; i++)
  {
    if (s[i] == '\\')
    {
      s = my_delete(s, i);
      end--;
    }
  }
  s = my_delete(s, begin);
  s = my_delete(s, end - 1);
  return s;
}

static char *dolar(char *s, int n)
{
  
}
*/
static void echo_not_e(int argc, char *args[])
{
  char *s = args[argc + 1];
  /*int len = strlen(s);
  
  int dquoted = search_dquoted(s, 1);
  if (dquoted > 0 && dquoted < len)
    s = in_dquoted(s, search_dquoted(s, 0), dquoted);
  
  int quoted = search_quoted(s, 1);
  if (quoted > 0 && quoted < len)
  {
    s = my_delete(s, quoted);
    s = my_delete(s, search_quoted(s, 0));
    s[len - 2] = '\0';
  }*/
  /*struct string_i S;
  S.i = 0;
  S.s = s;
  S = echo_one(S);*/
  printf("%s", s);
  for (int i = argc + 2; args[i]; i++)
  {
   /* S.i = 0;
    S.s = args[i];
    S = echo_one(S);*/
    printf(" %s", s);
  }
}

static int echo_arg(int n, int e, int argc, char *args[])
{
  if (e)
    echo_e(argc, args);
  else
    echo_not_e(argc, args);
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
