#include <stdio.h>
#include <stdlib.h>
#include "../include/tree.h"

int setenv(const char *name, const char *value, int overwrite);
int init_environment(void)
{
  int index = 0;
  while (environ[index])
  {
    for (unsigned i = 1; i < strlen(environ[index]); ++i)
    {
      if (environ[index][i] == '=')
      {
        char *name = malloc(sizeof (char) * (i + 1));
        char *value = malloc(sizeof (char) * (strlen(environ[index]) - i));
        if (!name || !value)
          return 1;
        name = strncpy(name, environ[index], i);
        value = strncpy(value, environ[index] + i + 1, strlen(environ[index]) - i - 1);
        add_word(ENV_VAR, NULL, name, value);
        break;
      }
    }
    index++;
  }
  add_word(ENV_VAR, NULL, "_", "/usr/bin/make");
  add_word(ENV_VAR, NULL, "OLDPWD", "");
  add_word(ENV_VAR, NULL, "SHLVL", "2");
  setenv("OLDPWD", "", 1);

  add_word(VAR, NULL, "PS1", "42sh$ ");
  add_word(VAR, NULL, "PS2", "> ");
  return 0;
}
