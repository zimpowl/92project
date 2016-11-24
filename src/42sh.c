#include "include/42sh.h"
static int command(char *s)
{
  init_lexer(s);
  struct ntree *tree = input_p();
  int res = read_a(tree);
  return res;
}

static int command_mode(int argc, char *argv[])
{
  if (argc == 2)
    errx(1, "-c: option requires an argument");
  return command(argv[2]);
}

static int script_mode(char *name)
{
  int fd = open(name, O_RDONLY);
  if (fd == -1)
    errx(1, "%s: No such file or directory", name);
  char line[256];
  line[0] = '\0';
  char buf[1];
  buf[0] = ' ';
  while (read(fd, buf, 1) > 0)
  {
    sprintf(line, "%s%c", line, buf[0]);
    buf[0] = ' ';
    fflush(NULL);
  }
  close(fd);
  return command(line);
}

static int ast_print(char *s)
{
  if (!s)
    return 1;
  init_lexer(s);
  struct ntree *tree = input_p();
  my_print_ntree(tree, NULL);
  if (tree)
    return 0;
  return 1;
}

//allow to destroy the btree first
//can be used too for the CTRL-Z anf CTRL-C keys
int end(int res)
{
  destroy_words();
  return res;
}

int main(int argc, char *argv[])
{
  init_environment();
  if (argc == 1)
    return end(0);
  if (!strcmp(argv[1], "-c"))
    return end(command_mode(argc, argv));
  if (!strcmp(argv[1], "--ast-print"))
    return end(ast_print(argv[2]));
  if (!strcmp(argv[1], "--norc"))
    return end(0);
  if (!fnmatch("--v*", argv[1], 0))
  {
    printf("Version 0.8\n");
    return end(0);
  }
  else
    return end(script_mode(argv[1]));
}
