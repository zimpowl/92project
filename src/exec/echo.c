#include <../include/executor.h>
#include <../lexer/header_lexer.h>

static void echo_e(int argc, char *args[])
{
  printf("%s", args[argc + 1]);
  for (int i = argc + 2; args[i]; i++)
  {
    printf(" %s", args[i]);
  }
}

static int echo_arg(int n, int e, int argc, char *args[])
{
  if (e)
    echo_e(argc, args);
  else
    printf("Pas de -e");
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
